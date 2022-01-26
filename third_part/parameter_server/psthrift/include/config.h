/*
 * @Company: TWL
 * @Author: xue jian
 * @Email: xuejian@kanzhun.com
 * @Date: 2019-08-19 15:13:01
 * @LastEditTime: 2019-09-07 09:58:18
 */
//
// Created by feng on 3/18/18.
//

#ifndef LISTDB_CONFIG2_H
#define LISTDB_CONFIG2_H

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <string>
#include <vector>
#include "logger.hpp"
#include "rocksdb/options.h"
#include "table/block_based/block_based_table_factory.h"
#include "logger.h"

struct Master2 {
    std::string ip;
    int port;

    Master2() : ip("127.0.0.1"), port(12345) {}
};

enum ServerMode : unsigned char { kModeMaster = 1, kModeSlave = 2 };

int parse_log_level(const std::string &level);

struct BaseConfig {
    int port;
    int master_port;
    ServerMode mode;
    Master2 master;
    int slave_retry_seconds;
    size_t write_buffer_size;
    size_t target_file_size_base;
    std::string data_dir;
    std::string wal_dir;
    std::string db_log_dir;
    std::string server_log;
    int log_level;
    int wal_ttl_seconds;
    size_t wal_size_limit_mb;
    int max_background_jobs;
    int use_direct_reads;
    int use_direct_io_for_flush_and_compaction;
    int threads;
    int filter_bits_per_key;
    size_t block_cache;
    size_t block_size;
    rocksdb::CompressionType compression;
    rocksdb::CompressionType bottommost_compression;
    std::vector<std::string> columnFamilies;
    int create_missing_column_families;
    std::string groupid;

    BaseConfig() {
        create_missing_column_families = 1;
        port = 5569;
        master_port = 0;
        mode = kModeMaster;  // master
        slave_retry_seconds = 1;
        filter_bits_per_key = 0;
        write_buffer_size = 128 * 1024 * 1024;
        target_file_size_base = 256 * 1024 * 1024;
        data_dir = "db_data";
        log_level = util::Logger::kLevelInfo;
        wal_dir = "";
        db_log_dir = "";
        server_log = "stdout";
        wal_ttl_seconds = 0;  // 2 days
        wal_size_limit_mb = 0;  // 5G
        use_direct_reads = 0;
        max_background_jobs = 0;
        use_direct_io_for_flush_and_compaction = 1;
        threads = 4;
        block_size = 1024 * 4;
        block_cache = 0;
        compression = rocksdb::kSnappyCompression;
        bottommost_compression = rocksdb::kZSTD;
    }

    virtual int setDBOptions(rocksdb::Options &options) {
        options.write_buffer_size = this->write_buffer_size;
        options.target_file_size_base = this->target_file_size_base;
        options.use_direct_io_for_flush_and_compaction = this->use_direct_io_for_flush_and_compaction == 1;
        //
        options.compaction_readahead_size = 1024 * 1024 * 2;
        options.compression = this->compression;
        options.bottommost_compression = this->bottommost_compression;
        options.wal_dir = this->wal_dir;
        options.db_log_dir = this->db_log_dir;
        if (this->wal_ttl_seconds > 0) options.WAL_ttl_seconds = this->wal_ttl_seconds;
        if (this->wal_size_limit_mb > 0) options.WAL_size_limit_MB = this->wal_size_limit_mb;

        if (this->max_background_jobs > 0) options.max_background_jobs = this->max_background_jobs;

        rocksdb::BlockBasedTableOptions table_options;
        // http://rocksdb.org/blog/2019/03/08/format-version-4.html
        // the default is 2.
        // change to 4 seems better
        table_options.format_version = 4;
        table_options.index_block_restart_interval = 16;
        if (this->block_cache == 0) {
            table_options.no_block_cache = true;
        } else {
            table_options.block_cache = rocksdb::NewLRUCache(this->block_cache);
        }
        if (this->filter_bits_per_key > 0) {
            // With this option turned on, we will not build bloom filters on the last level
            // which contains 90% of the database.
            options.optimize_filters_for_hits = true;
            table_options.filter_policy.reset(rocksdb::NewBloomFilterPolicy(this->filter_bits_per_key, false));
        }

        table_options.block_size = this->block_size;
        options.table_factory.reset(new rocksdb::BlockBasedTableFactory(table_options));

        // his setting disables looking up files in table cache, thus speeding up all queries.
        // This is always a good thing to set if your server has a big limit on open files.
        options.max_open_files = -1;
        options.use_direct_reads = this->use_direct_reads == 1;
        // master mode create_if_missing, for slave it's an error
        options.create_if_missing = this->mode == kModeMaster;
        options.create_missing_column_families = create_missing_column_families == 1;

        if (mkdir(data_dir) < 0 || mkdir(db_log_dir) < 0 || mkdir(wal_dir) < 0) return -1;
        return 0;
    }

    virtual int ParseLine(std::vector<std::string> &argv) = 0;

    virtual int PrintUsage() = 0;

    virtual int Version() = 0;

    int Parse(int argc, char **argv) {
        if (argc == 1) return 0;
        int j = 1;

        char *configfile = nullptr;  // 配置文件
        std::string options;         // 额外的命令行参数

        const std::string a1 = argv[1];
        if (a1 == "-v" || a1 == "--version") {
            return this->Version();
        } else if (a1 == "-h" || a1 == "--help") {
            return this->PrintUsage();
        } else if (argv[j][0] != '-' && argv[j][1] != '-') {
            configfile = argv[j];
            j++;
        }

        // copied from redis server.c
        // --port 6380 will generate the string "port 6380\n" to be parsed after the actual file name is parsed, if any.
        while (j != argc) {
            if (argv[j][0] == '-' && argv[j][1] == '-') {  // Option name
                options.append("\n");
                options.append(argv[j] + 2).append(" ");
            } else {  // Option argument
                options.append(argv[j]);
            }
            j++;
        }

        std::string config;
        if (configfile) {
            char buf[4096];
            FILE *fp;
            if ((fp = fopen(configfile, "r")) == nullptr) {
                logger->error("Fatal error, can't open config file '{}'", configfile);
                exit(1);
            }
            while (fgets(buf, sizeof(buf), fp) != nullptr) {
                config.append(buf);
            }
            fclose(fp);
        }

        if (!options.empty()) config.append(options).append("\n");
        return loadConfigFromString(config);
    }

    int loadConfigFromString(const std::string &config) {
        std::vector<std::string> lines;
        SplitString(config, lines, "\n");

        for (auto &line : lines) {
            std::vector<std::string> argv;
            line = trim(line);
            if (line.empty() || line[0] == '#' || (line[0] == '/' && line[1] == '/')) continue;
            strsplitargs(line, argv);
            if (argv.empty()) {
                continue;
            }
            strtolower(argv[0]);

            if (this->ParseLine(argv) >= 0) continue;  // 子类handle了

            if ("port" == argv[0] && argv.size() == 2) {
                this->port = std::atoi(argv[1].data());
                if (this->port < 0 || this->port > 65535) {
                    logger->error("Invalid port value : {}", this->port);
                    exit(1);
                }
            } else if ("master_port" == argv[0] && argv.size() == 2) {
                this->master_port = std::atoi(argv[1].data());
                if (this->master_port < 0 || this->master_port > 65535) {
                    logger->error("Invalid master_port value : {}", this->master_port);
                    exit(1);
                }
            } else if ("mode" == argv[0] && argv.size() == 2) {
                if (argv[1] == "master")
                    this->mode = kModeMaster;
                else if (argv[1] == "slave")
                    this->mode = kModeSlave;
                else {
                    logger->error("Invalid mode : {} must master or slave!", argv[1].data());
                    exit(1);
                }
            } else if ("slaveof" == argv[0] && argv.size() == 3) {
                this->master.ip = argv[1];
                this->master.port = std::atoi(argv[2].data());
            } else if ("write_buffer_size" == argv[0] && argv.size() == 2) {
                this->write_buffer_size = memtoll(argv[1]);
            } else if ("target_file_size_base" == argv[0] && argv.size() == 2) {
                this->target_file_size_base = memtoll(argv[1]);
            } else if ("block_cache" == argv[0] && argv.size() == 2) {
                this->block_cache = memtoll(argv[1]);
            } else if ("block_size" == argv[0] && argv.size() == 2) {
                this->block_size = memtoll(argv[1]);
            } else if ("compression" == argv[0] && argv.size() == 2) {
                this->compression = parse_compression(argv[1]);
            } else if ("bottommost_compression" == argv[0] && argv.size() == 2) {
                this->bottommost_compression = parse_compression(argv[1]);
            } else if ("data_dir" == argv[0] && argv.size() == 2) {
                this->data_dir = argv[1];
            } else if ("db_log_dir" == argv[0] && argv.size() == 2) {
                this->db_log_dir = argv[1];
            } else if ("wal_dir" == argv[0] && argv.size() == 2) {
                this->wal_dir = argv[1];
            } else if ("server_log" == argv[0] && argv.size() >= 2) {
                this->server_log = argv[1];
                if (argv.size() == 3) this->log_level = parse_log_level(argv[2]);
            } else if ("max_background_jobs" == argv[0] && argv.size() == 2) {
                this->max_background_jobs = std::atoi(argv[1].data());
            } else if ("wal_ttl_seconds" == argv[0] && argv.size() == 2) {
                this->wal_ttl_seconds = std::atoi(argv[1].data());
            } else if ("wal_size_limit_mb" == argv[0] && argv.size() == 2) {
                this->wal_size_limit_mb = std::atoi(argv[1].data());
            } else if ("create_missing_column_families" == argv[0] && argv.size() == 2) {
                if ((this->create_missing_column_families = booltoi(argv[1].data())) == -1) {
                    logger->error("create_missing_column_families must be 'true' or 'false' : {}", argv[1].data());
                    exit(1);
                }
            } else if ("column_family" == argv[0] && argv.size() == 2) {
                SplitString(argv[1], this->columnFamilies, ",");
            } else if ("slave_retry_seconds" == argv[0] && argv.size() == 2) {
                this->slave_retry_seconds = std::atoi(argv[1].data());
            } else if ("use_direct_reads" == argv[0] && argv.size() == 2) {
                if ((this->use_direct_reads = booltoi(argv[1].data())) == -1) {
                    logger->error("argument must be 'true' or 'false' : {}", argv[1].data());
                    exit(1);
                }
            } else if ("use_direct_io_for_flush_and_compaction" == argv[0] && argv.size() == 2) {
                if ((this->use_direct_io_for_flush_and_compaction = booltoi(argv[1].data())) == -1) {
                    logger->error("argument must be 'true' or 'false': {}", argv[1].data());
                    exit(1);
                }
            } else if ("threads" == argv[0] && argv.size() == 2) {
                this->threads = std::atoi(argv[1].data());
                if (this->threads <= 0) {
                    logger->error("threads must be 1 or greater : {}", argv[1].data());
                    exit(1);
                }
            }else if ("groupid" == argv[0] && argv.size() == 2) {
                this->groupid = argv[1];
            }
        }
        return 0;
    }

    void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c) {
        std::string::size_type pos1, pos2;
        pos2 = s.find(c);
        pos1 = 0;
        while (std::string::npos != pos2) {
            if (pos2 > pos1) {
                v.push_back(s.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if (pos1 != s.length()) v.push_back(s.substr(pos1));
    }

    std::string &trim(std::string &text) {
        if (!text.empty()) {
            text.erase(0, text.find_first_not_of(" \n\r\t"));
            text.erase(text.find_last_not_of(" \n\r\t") + 1);
        }
        return text;
    }

    void strsplitargs(std::string &s, std::vector<std::string> &v) {
        for (size_t i = 0; i != s.size(); i++) {
            if (s[i] == '\t') s[i] = ' ';
        }
        SplitString(s, v, " ");
    }

    void strtolower(std::string &s) { std::transform(s.begin(), s.end(), s.begin(), ::tolower); }

    rocksdb::CompressionType parse_compression(const std::string &c) {
        if (c == "snappy") return rocksdb::kSnappyCompression;
        if (c == "zlib") return rocksdb::kZlibCompression;
        if (c == "bzip2") return rocksdb::kBZip2Compression;
        if (c == "lz4") return rocksdb::kLZ4Compression;
        if (c == "zstd") return rocksdb::kZSTD;
        return rocksdb::kNoCompression;
    }

    int booltoi(const char *s) {
        if (!strcasecmp(s, "true"))
            return 1;
        else if (!strcasecmp(s, "false"))
            return 0;
        else
            return -1;
    }

    size_t memtoll(const std::string &p) {
        size_t mul = 1;
        size_t val = 0;

        size_t i = 0;
        while (i != p.size() && isdigit(p[i])) i++;
        if ("k" == p.substr(i)) {
            mul = 1024;
        } else if ("m" == p.substr(i)) {
            mul = 1024 * 1024;
        } else if ("g" == p.substr(i)) {
            mul = 1024 * 1024 * 1024;
        } else if (i != p.size()) {
            logger->error("error arg in mem: {}", p.data());
            exit(1);
        }
        if (i == 0) {
            logger->error("error arg in mem: {}", p.data());
            exit(1);
        }
        val = std::stoll(p.substr(0, i));
        return val * mul;
    }

   private:
    int mkdir(const std::string &dir) {
        rocksdb::Status status;
        rocksdb::Env *env = rocksdb::Env::Default();
        if (!dir.empty() && !env->FileExists(dir).ok() && !(status = env->CreateDir(dir)).ok()) {
            logger->error("dir: {} does not exits, can't create: {}, exit", dir.data(), status.ToString().data());
            return -1;
        }
        return 0;
    }
};

#endif  // LISTDB_CONFIG2_H
