licenses(["notice"])
# Most of these settings are taken from https://github.com/facebook/rocksdb/blob/master/buckifier/targets_cfg.py

rocksdb_defines = [
    "OS_LINUX",
    "ROCKSDB_FALLOCATE_PRESENT",
    "ROCKSDB_PLATFORM_POSIX",
    "ROCKSDB_LIB_IO_POSIX",
    "ROCKSDB_SUPPORT_THREAD_LOCAL",
    "ROCKSDB_MALLOC_USABLE_SIZE",
    "ROCKSDB_PTHREAD_ADAPTIVE_MUTEX",
    "ROCKSDB_RANGESYNC_PRESENT",
    "ROCKSDB_SCHED_GETCPU_PRESENT",
    "HAVE_SSE42",
    "ROCKSDB_NO_DYNAMIC_EXTENSION",
    "GFLAGS",
] + ["SUPPORT_CLOCK_CACHE"]

genrule(
    name = "build_version",
    srcs = glob([".git/**/*"]) + [
        "util/build_version.cc.in",
    ],
    outs = [
        "util/build_version.cc",
    ],
    # This used to parse the git repo, but cloning the repo is slow, so we switched this
    # to download the tar. We just make up versions for all this stuff.
    cmd = "sed -e s/@@GIT_SHA@@/GHOST_HEAD/ -e s/@@GIT_DATE_TIME@@/$$(date +%F)/ " +
          "external/com_github_facebook_rocksdb/util/build_version.cc.in >> $(@)",
)

cc_library(
    name = "rocksdb",
    srcs = [":build_version"] + [
        "cache/cache_helpers.h",
        "cache/clock_cache.h",
        "cache/lru_cache.h",
        "cache/sharded_cache.h",
        "db/arena_wrapped_db_iter.h",
        "db/blob/blob_constants.h",
        "db/blob/blob_file_addition.h",
        "db/blob/blob_file_builder.h",
        "db/blob/blob_file_cache.h",
        "db/blob/blob_file_garbage.h",
        "db/blob/blob_file_meta.h",
        "db/blob/blob_file_reader.h",
        "db/blob/blob_index.h",
        "db/blob/blob_log_format.h",
        "db/blob/blob_log_sequential_reader.h",
        "db/blob/blob_log_writer.h",
        "db/builder.h",
        "db/column_family.h",
        "db/compacted_db_impl.h",
        "db/compaction/compaction.h",
        "db/compaction/compaction_iteration_stats.h",
        "db/compaction/compaction_iterator.h",
        "db/compaction/compaction_job.h",
        "db/compaction/compaction_picker.h",
        "db/compaction/compaction_picker_fifo.h",
        "db/compaction/compaction_picker_level.h",
        "db/compaction/compaction_picker_universal.h",
        "db/db_impl/db_impl.h",
        "db/db_impl/db_impl_readonly.h",
        "db/db_impl/db_impl_secondary.h",
        "db/db_info_dumper.h",
        "db/db_iter.h",
        "db/dbformat.h",
        "db/error_handler.h",
        "db/event_helpers.h",
        "db/external_sst_file_ingestion_job.h",
        "db/file_indexer.h",
        "db/flush_job.h",
        "db/flush_scheduler.h",
        "db/forward_iterator.h",
        "db/import_column_family_job.h",
        "db/internal_stats.h",
        "db/job_context.h",
        "db/log_format.h",
        "db/log_reader.h",
        "db/log_writer.h",
        "db/logs_with_prep_tracker.h",
        "db/lookup_key.h",
        "db/malloc_stats.h",
        "db/memtable.h",
        "db/memtable_list.h",
        "db/merge_context.h",
        "db/merge_helper.h",
        "db/output_validator.h",
        "db/periodic_work_scheduler.h",
        "db/pinned_iterators_manager.h",
        "db/pre_release_callback.h",
        "db/range_del_aggregator.h",
        "db/range_tombstone_fragmenter.h",
        "db/read_callback.h",
        "db/snapshot_checker.h",
        "db/snapshot_impl.h",
        "db/table_cache.h",
        "db/table_properties_collector.h",
        "db/transaction_log_impl.h",
        "db/trim_history_scheduler.h",
        "db/version_builder.h",
        "db/version_edit.h",
        "db/version_edit_handler.h",
        "db/version_set.h",
        "db/wal_edit.h",
        "db/wal_manager.h",
        "db/write_batch_internal.h",
        "db/write_callback.h",
        "db/write_controller.h",
        "db/write_thread.h",
        "env/composite_env_wrapper.h",
        "env/env_chroot.h",
        "env/env_encryption_ctr.h",
        "env/file_system_tracer.h",
        "env/io_posix.h",
        "env/mock_env.h",
        "file/delete_scheduler.h",
        "file/file_prefetch_buffer.h",
        "file/file_util.h",
        "file/filename.h",
        "file/random_access_file_reader.h",
        "file/read_write_util.h",
        "file/readahead_raf.h",
        "file/sequence_file_reader.h",
        "file/sst_file_manager_impl.h",
        "file/writable_file_writer.h",
        "hdfs/env_hdfs.h",
        "logging/auto_roll_logger.h",
        "logging/env_logger.h",
        "logging/event_logger.h",
        "logging/log_buffer.h",
        "logging/logging.h",
        "logging/posix_logger.h",
        "memory/allocator.h",
        "memory/arena.h",
        "memory/concurrent_arena.h",
        "memory/jemalloc_nodump_allocator.h",
        "memory/memkind_kmem_allocator.h",
        "memory/memory_allocator.h",
        "memory/memory_usage.h",
        "memtable/hash_linklist_rep.h",
        "memtable/hash_skiplist_rep.h",
        "memtable/inlineskiplist.h",
        "memtable/skiplist.h",
        "memtable/stl_wrappers.h",
        "monitoring/file_read_sample.h",
        "monitoring/histogram.h",
        "monitoring/histogram_windowing.h",
        "monitoring/in_memory_stats_history.h",
        "monitoring/instrumented_mutex.h",
        "monitoring/iostats_context_imp.h",
        "monitoring/perf_context_imp.h",
        "monitoring/perf_level_imp.h",
        "monitoring/perf_step_timer.h",
        "monitoring/persistent_stats_history.h",
        "monitoring/statistics.h",
        "monitoring/thread_status_updater.h",
        "monitoring/thread_status_util.h",
        "options/cf_options.h",
        "options/configurable_helper.h",
        "options/customizable_helper.h",
        "options/db_options.h",
        "options/options_helper.h",
        "options/options_parser.h",
        "port/jemalloc_helper.h",
        "port/lang.h",
        "port/likely.h",
        "port/malloc.h",
        "port/port.h",
        "port/port_dirent.h",
        "port/port_posix.h",
        "port/stack_trace.h",
        "port/sys_time.h",
        "port/util_logger.h",
        "port/xpress.h",
        "table/adaptive/adaptive_table_factory.h",
        "table/block_based/binary_search_index_reader.h",
        "table/block_based/block.h",
        "table/block_based/block_based_filter_block.h",
        "table/block_based/block_based_table_builder.h",
        "table/block_based/block_based_table_factory.h",
        "table/block_based/block_based_table_iterator.h",
        "table/block_based/block_based_table_reader.h",
        "table/block_based/block_based_table_reader_impl.h",
        "table/block_based/block_builder.h",
        "table/block_based/block_prefetcher.h",
        "table/block_based/block_prefix_index.h",
        "table/block_based/block_type.h",
        "table/block_based/cachable_entry.h",
        "table/block_based/data_block_footer.h",
        "table/block_based/data_block_hash_index.h",
        "table/block_based/filter_block.h",
        "table/block_based/filter_block_reader_common.h",
        "table/block_based/filter_policy_internal.h",
        "table/block_based/flush_block_policy.h",
        "table/block_based/full_filter_block.h",
        "table/block_based/hash_index_reader.h",
        "table/block_based/index_builder.h",
        "table/block_based/index_reader_common.h",
        "table/block_based/parsed_full_filter_block.h",
        "table/block_based/partitioned_filter_block.h",
        "table/block_based/partitioned_index_iterator.h",
        "table/block_based/partitioned_index_reader.h",
        "table/block_based/reader_common.h",
        "table/block_based/uncompression_dict_reader.h",
        "table/block_fetcher.h",
        "table/cuckoo/cuckoo_table_builder.h",
        "table/cuckoo/cuckoo_table_factory.h",
        "table/cuckoo/cuckoo_table_reader.h",
        "table/format.h",
        "table/get_context.h",
        "table/internal_iterator.h",
        "table/iter_heap.h",
        "table/iterator_wrapper.h",
        "table/merging_iterator.h",
        "table/meta_blocks.h",
        "table/multiget_context.h",
        "table/persistent_cache_helper.h",
        "table/persistent_cache_options.h",
        "table/plain/plain_table_bloom.h",
        "table/plain/plain_table_builder.h",
        "table/plain/plain_table_factory.h",
        "table/plain/plain_table_index.h",
        "table/plain/plain_table_key_coding.h",
        "table/plain/plain_table_reader.h",
        "table/scoped_arena_iterator.h",
        "table/sst_file_dumper.h",
        "table/sst_file_writer_collectors.h",
        "table/table_builder.h",
        "table/table_properties_internal.h",
        "table/table_reader.h",
        "table/table_reader_caller.h",
        "table/two_level_iterator.h",
        "test_util/mock_time_env.h",
        "test_util/sync_point.h",
        "test_util/sync_point_impl.h",
        "test_util/transaction_test_util.h",
        "third-party/folly/folly/ConstexprMath.h",
        "tools/block_cache_analyzer/block_cache_trace_analyzer.h",
        "tools/ldb_cmd_impl.h",
        "tools/trace_analyzer_tool.h",
        "trace_replay/block_cache_tracer.h",
        "trace_replay/io_tracer.h",
        "trace_replay/trace_replay.h",
        "util/aligned_buffer.h",
        "util/autovector.h",
        "util/bloom_impl.h",
        "util/build_version.h",
        "util/cast_util.h",
        "util/channel.h",
        "util/coding.h",
        "util/coding_lean.h",
        "util/compression.h",
        "util/compression_context_cache.h",
        "util/concurrent_task_limiter_impl.h",
        "util/core_local.h",
        "util/crc32c.h",
        "util/crc32c_arm64.h",
        "util/crc32c_ppc.h",
        "util/crc32c_ppc_constants.h",
        "util/duplicate_detector.h",
        "util/dynamic_bloom.h",
        "util/fastrange.h",
        "util/file_checksum_helper.h",
        "util/gflags_compat.h",
        "util/hash.h",
        "util/hash_map.h",
        "util/heap.h",
        "util/kv_map.h",
        "util/math.h",
        "util/math128.h",
        "util/murmurhash.h",
        "util/mutexlock.h",
        "util/ppc-opcode.h",
        "util/random.h",
        "util/rate_limiter.h",
        "util/repeatable_thread.h",
        "util/ribbon_impl.h",
        "util/set_comparator.h",
        "util/stderr_logger.h",
        "util/stop_watch.h",
        "util/string_util.h",
        "util/thread_local.h",
        "util/thread_operation.h",
        "util/threadpool_imp.h",
        "util/timer.h",
        "util/timer_queue.h",
        "util/user_comparator_wrapper.h",
        "util/vector_iterator.h",
        "util/work_queue.h",
        "util/xxh3p.h",
        "util/xxhash.h",
        "utilities/blob_db/blob_compaction_filter.h",
        "utilities/blob_db/blob_db.h",
        "utilities/blob_db/blob_db_gc_stats.h",
        "utilities/blob_db/blob_db_impl.h",
        "utilities/blob_db/blob_db_iterator.h",
        "utilities/blob_db/blob_db_listener.h",
        "utilities/blob_db/blob_dump_tool.h",
        "utilities/blob_db/blob_file.h",
        "utilities/checkpoint/checkpoint_impl.h",
        "utilities/compaction_filters/remove_emptyvalue_compactionfilter.h",
        "utilities/merge_operators.h",
        "utilities/merge_operators/bytesxor.h",
        "utilities/merge_operators/sortlist.h",
        "utilities/merge_operators/string_append/stringappend.h",
        "utilities/merge_operators/string_append/stringappend2.h",
        "utilities/persistent_cache/block_cache_tier.h",
        "utilities/persistent_cache/block_cache_tier_file.h",
        "utilities/persistent_cache/block_cache_tier_file_buffer.h",
        "utilities/persistent_cache/block_cache_tier_metadata.h",
        "utilities/persistent_cache/hash_table.h",
        "utilities/persistent_cache/hash_table_evictable.h",
        "utilities/persistent_cache/lrulist.h",
        "utilities/persistent_cache/persistent_cache_tier.h",
        "utilities/persistent_cache/persistent_cache_util.h",
        "utilities/persistent_cache/volatile_tier_impl.h",
        "utilities/simulator_cache/cache_simulator.h",
        "utilities/table_properties_collectors/compact_on_deletion_collector.h",
        "utilities/trace/file_trace_reader_writer.h",
        "utilities/transactions/lock/lock_manager.h",
        "utilities/transactions/lock/lock_tracker.h",
        "utilities/transactions/lock/point/point_lock_manager.h",
        "utilities/transactions/lock/point/point_lock_tracker.h",
        "utilities/transactions/optimistic_transaction.h",
        "utilities/transactions/optimistic_transaction_db_impl.h",
        "utilities/transactions/pessimistic_transaction.h",
        "utilities/transactions/pessimistic_transaction_db.h",
        "utilities/transactions/transaction_base.h",
        "utilities/transactions/transaction_db_mutex_impl.h",
        "utilities/transactions/transaction_util.h",
        "utilities/transactions/write_prepared_txn.h",
        "utilities/transactions/write_prepared_txn_db.h",
        "utilities/transactions/write_unprepared_txn.h",
        "utilities/transactions/write_unprepared_txn_db.h",
        "utilities/ttl/db_ttl_impl.h",
        "utilities/write_batch_with_index/write_batch_with_index_internal.h",
    ] + [
        "cache/cache.cc",
        "cache/clock_cache.cc",
        "cache/lru_cache.cc",
        "cache/sharded_cache.cc",
        "db/arena_wrapped_db_iter.cc",
        "db/blob/blob_file_addition.cc",
        "db/blob/blob_file_builder.cc",
        "db/blob/blob_file_cache.cc",
        "db/blob/blob_file_garbage.cc",
        "db/blob/blob_file_meta.cc",
        "db/blob/blob_file_reader.cc",
        "db/blob/blob_log_format.cc",
        "db/blob/blob_log_sequential_reader.cc",
        "db/blob/blob_log_writer.cc",
        "db/builder.cc",
        "db/c.cc",
        "db/column_family.cc",
        "db/compacted_db_impl.cc",
        "db/compaction/compaction.cc",
        "db/compaction/compaction_iterator.cc",
        "db/compaction/compaction_job.cc",
        "db/compaction/compaction_picker.cc",
        "db/compaction/compaction_picker_fifo.cc",
        "db/compaction/compaction_picker_level.cc",
        "db/compaction/compaction_picker_universal.cc",
        "db/compaction/sst_partitioner.cc",
        "db/convenience.cc",
        "db/db_filesnapshot.cc",
        "db/db_impl/db_impl.cc",
        "db/db_impl/db_impl_compaction_flush.cc",
        "db/db_impl/db_impl_debug.cc",
        "db/db_impl/db_impl_experimental.cc",
        "db/db_impl/db_impl_files.cc",
        "db/db_impl/db_impl_open.cc",
        "db/db_impl/db_impl_readonly.cc",
        "db/db_impl/db_impl_secondary.cc",
        "db/db_impl/db_impl_write.cc",
        "db/db_info_dumper.cc",
        "db/db_iter.cc",
        "db/dbformat.cc",
        "db/error_handler.cc",
        "db/event_helpers.cc",
        "db/experimental.cc",
        "db/external_sst_file_ingestion_job.cc",
        "db/file_indexer.cc",
        "db/flush_job.cc",
        "db/flush_scheduler.cc",
        "db/forward_iterator.cc",
        "db/import_column_family_job.cc",
        "db/internal_stats.cc",
        "db/log_reader.cc",
        "db/log_writer.cc",
        "db/logs_with_prep_tracker.cc",
        "db/malloc_stats.cc",
        "db/memtable.cc",
        "db/memtable_list.cc",
        "db/merge_helper.cc",
        "db/merge_operator.cc",
        "db/output_validator.cc",
        "db/periodic_work_scheduler.cc",
        "db/range_del_aggregator.cc",
        "db/range_tombstone_fragmenter.cc",
        "db/repair.cc",
        "db/snapshot_impl.cc",
        "db/table_cache.cc",
        "db/table_properties_collector.cc",
        "db/transaction_log_impl.cc",
        "db/trim_history_scheduler.cc",
        "db/version_builder.cc",
        "db/version_edit.cc",
        "db/version_edit_handler.cc",
        "db/version_set.cc",
        "db/wal_edit.cc",
        "db/wal_manager.cc",
        "db/write_batch.cc",
        "db/write_batch_base.cc",
        "db/write_controller.cc",
        "db/write_thread.cc",
        "env/env.cc",
        "env/env_chroot.cc",
        "env/env_encryption.cc",
        "env/env_hdfs.cc",
        "env/env_posix.cc",
        "env/file_system.cc",
        "env/file_system_tracer.cc",
        "env/fs_posix.cc",
        "env/io_posix.cc",
        "env/mock_env.cc",
        "file/delete_scheduler.cc",
        "file/file_prefetch_buffer.cc",
        "file/file_util.cc",
        "file/filename.cc",
        "file/random_access_file_reader.cc",
        "file/read_write_util.cc",
        "file/readahead_raf.cc",
        "file/sequence_file_reader.cc",
        "file/sst_file_manager_impl.cc",
        "file/writable_file_writer.cc",
        "logging/auto_roll_logger.cc",
        "logging/event_logger.cc",
        "logging/log_buffer.cc",
        "memory/arena.cc",
        "memory/concurrent_arena.cc",
        "memory/jemalloc_nodump_allocator.cc",
        "memtable/alloc_tracker.cc",
        "memtable/hash_linklist_rep.cc",
        "memtable/hash_skiplist_rep.cc",
        "memtable/skiplistrep.cc",
        "memtable/vectorrep.cc",
        "memtable/write_buffer_manager.cc",
        "monitoring/histogram.cc",
        "monitoring/histogram_windowing.cc",
        "monitoring/in_memory_stats_history.cc",
        "monitoring/instrumented_mutex.cc",
        "monitoring/iostats_context.cc",
        "monitoring/perf_context.cc",
        "monitoring/perf_level.cc",
        "monitoring/persistent_stats_history.cc",
        "monitoring/statistics.cc",
        "monitoring/thread_status_impl.cc",
        "monitoring/thread_status_updater.cc",
        "monitoring/thread_status_updater_debug.cc",
        "monitoring/thread_status_util.cc",
        "monitoring/thread_status_util_debug.cc",
        "options/cf_options.cc",
        "options/configurable.cc",
        "options/customizable.cc",
        "options/db_options.cc",
        "options/options.cc",
        "options/options_helper.cc",
        "options/options_parser.cc",
        "port/port_posix.cc",
        "port/stack_trace.cc",
        "table/adaptive/adaptive_table_factory.cc",
        "table/block_based/binary_search_index_reader.cc",
        "table/block_based/block.cc",
        "table/block_based/block_based_filter_block.cc",
        "table/block_based/block_based_table_builder.cc",
        "table/block_based/block_based_table_factory.cc",
        "table/block_based/block_based_table_iterator.cc",
        "table/block_based/block_based_table_reader.cc",
        "table/block_based/block_builder.cc",
        "table/block_based/block_prefetcher.cc",
        "table/block_based/block_prefix_index.cc",
        "table/block_based/data_block_footer.cc",
        "table/block_based/data_block_hash_index.cc",
        "table/block_based/filter_block_reader_common.cc",
        "table/block_based/filter_policy.cc",
        "table/block_based/flush_block_policy.cc",
        "table/block_based/full_filter_block.cc",
        "table/block_based/hash_index_reader.cc",
        "table/block_based/index_builder.cc",
        "table/block_based/index_reader_common.cc",
        "table/block_based/parsed_full_filter_block.cc",
        "table/block_based/partitioned_filter_block.cc",
        "table/block_based/partitioned_index_iterator.cc",
        "table/block_based/partitioned_index_reader.cc",
        "table/block_based/reader_common.cc",
        "table/block_based/uncompression_dict_reader.cc",
        "table/block_fetcher.cc",
        "table/cuckoo/cuckoo_table_builder.cc",
        "table/cuckoo/cuckoo_table_factory.cc",
        "table/cuckoo/cuckoo_table_reader.cc",
        "table/format.cc",
        "table/get_context.cc",
        "table/iterator.cc",
        "table/merging_iterator.cc",
        "table/meta_blocks.cc",
        "table/persistent_cache_helper.cc",
        "table/plain/plain_table_bloom.cc",
        "table/plain/plain_table_builder.cc",
        "table/plain/plain_table_factory.cc",
        "table/plain/plain_table_index.cc",
        "table/plain/plain_table_key_coding.cc",
        "table/plain/plain_table_reader.cc",
        "table/sst_file_dumper.cc",
        "table/sst_file_reader.cc",
        "table/sst_file_writer.cc",
        "table/table_factory.cc",
        "table/table_properties.cc",
        "table/two_level_iterator.cc",
        "test_util/sync_point.cc",
        "test_util/sync_point_impl.cc",
        "test_util/transaction_test_util.cc",
        "tools/dump/db_dump_tool.cc",
        "tools/ldb_cmd.cc",
        "tools/ldb_tool.cc",
        "tools/sst_dump_tool.cc",
        "trace_replay/block_cache_tracer.cc",
        "trace_replay/io_tracer.cc",
        "trace_replay/trace_replay.cc",
        "util/coding.cc",
        "util/compaction_job_stats_impl.cc",
        "util/comparator.cc",
        "util/compression_context_cache.cc",
        "util/concurrent_task_limiter_impl.cc",
        "util/crc32c.cc",
        "util/crc32c_arm64.cc",
        "util/dynamic_bloom.cc",
        "util/file_checksum_helper.cc",
        "util/hash.cc",
        "util/murmurhash.cc",
        "util/random.cc",
        "util/rate_limiter.cc",
        "util/ribbon_alg.h",
        "util/slice.cc",
        "util/status.cc",
        "util/string_util.cc",
        "util/thread_local.cc",
        "util/threadpool_imp.cc",
        "util/xxhash.cc",
        "utilities/backupable/backupable_db.cc",
        "utilities/blob_db/blob_compaction_filter.cc",
        "utilities/blob_db/blob_db.cc",
        "utilities/blob_db/blob_db_impl.cc",
        "utilities/blob_db/blob_db_impl_filesnapshot.cc",
        "utilities/blob_db/blob_dump_tool.cc",
        "utilities/blob_db/blob_file.cc",
        "utilities/checkpoint/checkpoint_impl.cc",
        "utilities/compaction_filters/layered_compaction_filter_base.h",
        "utilities/compaction_filters/remove_emptyvalue_compactionfilter.cc",
        "utilities/convenience/info_log_finder.cc",
        "utilities/debug.cc",
        "utilities/env_mirror.cc",
        "utilities/env_timed.cc",
        "utilities/leveldb_options/leveldb_options.cc",
        "utilities/memory/memory_util.cc",
        "utilities/merge_operators/bytesxor.cc",
        "utilities/merge_operators/max.cc",
        "utilities/merge_operators/put.cc",
        "utilities/merge_operators/sortlist.cc",
        "utilities/merge_operators/string_append/stringappend.cc",
        "utilities/merge_operators/string_append/stringappend2.cc",
        "utilities/merge_operators/uint64add.cc",
        "utilities/object_registry.cc",
        "utilities/option_change_migration/option_change_migration.cc",
        "utilities/options/options_util.cc",
        "utilities/persistent_cache/block_cache_tier.cc",
        "utilities/persistent_cache/block_cache_tier_file.cc",
        "utilities/persistent_cache/block_cache_tier_metadata.cc",
        "utilities/persistent_cache/persistent_cache_tier.cc",
        "utilities/persistent_cache/volatile_tier_impl.cc",
        "utilities/simulator_cache/cache_simulator.cc",
        "utilities/simulator_cache/sim_cache.cc",
        "utilities/table_properties_collectors/compact_on_deletion_collector.cc",
        "utilities/trace/file_trace_reader_writer.cc",
        "utilities/transactions/lock/lock_manager.cc",
        "utilities/transactions/lock/point/point_lock_manager.cc",
        "utilities/transactions/lock/point/point_lock_tracker.cc",
        "utilities/transactions/optimistic_transaction.cc",
        "utilities/transactions/optimistic_transaction_db_impl.cc",
        "utilities/transactions/pessimistic_transaction.cc",
        "utilities/transactions/pessimistic_transaction_db.cc",
        "utilities/transactions/snapshot_checker.cc",
        "utilities/transactions/transaction_base.cc",
        "utilities/transactions/transaction_db_mutex_impl.cc",
        "utilities/transactions/transaction_util.cc",
        "utilities/transactions/write_prepared_txn.cc",
        "utilities/transactions/write_prepared_txn_db.cc",
        "utilities/transactions/write_unprepared_txn.cc",
        "utilities/transactions/write_unprepared_txn_db.cc",
        "utilities/ttl/db_ttl_impl.cc",
        "utilities/write_batch_with_index/write_batch_with_index.cc",
        "utilities/write_batch_with_index/write_batch_with_index_internal.cc",
    ],
    hdrs = [
        "include/rocksdb/advanced_options.h",
        "include/rocksdb/c.h",
        "include/rocksdb/cache.h",
        "include/rocksdb/cleanable.h",
        "include/rocksdb/compaction_filter.h",
        "include/rocksdb/compaction_job_stats.h",
        "include/rocksdb/comparator.h",
        "include/rocksdb/compression_type.h",
        "include/rocksdb/concurrent_task_limiter.h",
        "include/rocksdb/configurable.h",
        "include/rocksdb/convenience.h",
        "include/rocksdb/customizable.h",
        "include/rocksdb/db.h",
        "include/rocksdb/db_bench_tool.h",
        "include/rocksdb/db_dump_tool.h",
        "include/rocksdb/db_stress_tool.h",
        "include/rocksdb/env.h",
        "include/rocksdb/env_encryption.h",
        "include/rocksdb/experimental.h",
        "include/rocksdb/file_checksum.h",
        "include/rocksdb/file_system.h",
        "include/rocksdb/filter_policy.h",
        "include/rocksdb/flush_block_policy.h",
        "include/rocksdb/io_status.h",
        "include/rocksdb/iostats_context.h",
        "include/rocksdb/iterator.h",
        "include/rocksdb/ldb_tool.h",
        "include/rocksdb/listener.h",
        "include/rocksdb/memory_allocator.h",
        "include/rocksdb/memtablerep.h",
        "include/rocksdb/merge_operator.h",
        "include/rocksdb/metadata.h",
        "include/rocksdb/options.h",
        "include/rocksdb/perf_context.h",
        "include/rocksdb/perf_level.h",
        "include/rocksdb/persistent_cache.h",
        "include/rocksdb/rate_limiter.h",
        "include/rocksdb/rocksdb_namespace.h",
        "include/rocksdb/slice.h",
        "include/rocksdb/slice_transform.h",
        "include/rocksdb/snapshot.h",
        "include/rocksdb/sst_dump_tool.h",
        "include/rocksdb/sst_file_manager.h",
        "include/rocksdb/sst_file_reader.h",
        "include/rocksdb/sst_file_writer.h",
        "include/rocksdb/sst_partitioner.h",
        "include/rocksdb/statistics.h",
        "include/rocksdb/stats_history.h",
        "include/rocksdb/status.h",
        "include/rocksdb/table.h",
        "include/rocksdb/table_properties.h",
        "include/rocksdb/thread_status.h",
        "include/rocksdb/threadpool.h",
        "include/rocksdb/trace_reader_writer.h",
        "include/rocksdb/transaction_log.h",
        "include/rocksdb/types.h",
        "include/rocksdb/universal_compaction.h",
        "include/rocksdb/utilities/backupable_db.h",
        "include/rocksdb/utilities/checkpoint.h",
        "include/rocksdb/utilities/convenience.h",
        "include/rocksdb/utilities/db_ttl.h",
        "include/rocksdb/utilities/debug.h",
        "include/rocksdb/utilities/env_mirror.h",
        "include/rocksdb/utilities/info_log_finder.h",
        "include/rocksdb/utilities/ldb_cmd.h",
        "include/rocksdb/utilities/ldb_cmd_execute_result.h",
        "include/rocksdb/utilities/leveldb_options.h",
        "include/rocksdb/utilities/memory_util.h",
        "include/rocksdb/utilities/object_registry.h",
        "include/rocksdb/utilities/optimistic_transaction_db.h",
        "include/rocksdb/utilities/option_change_migration.h",
        "include/rocksdb/utilities/options_type.h",
        "include/rocksdb/utilities/options_util.h",
        "include/rocksdb/utilities/sim_cache.h",
        "include/rocksdb/utilities/stackable_db.h",
        "include/rocksdb/utilities/table_properties_collectors.h",
        "include/rocksdb/utilities/transaction.h",
        "include/rocksdb/utilities/transaction_db.h",
        "include/rocksdb/utilities/transaction_db_mutex.h",
        "include/rocksdb/utilities/utility_db.h",
        "include/rocksdb/utilities/write_batch_with_index.h",
        "include/rocksdb/version.h",
        "include/rocksdb/wal_filter.h",
        "include/rocksdb/write_batch.h",
        "include/rocksdb/write_batch_base.h",
        "include/rocksdb/write_buffer_manager.h",
    ],
    copts = ["-msse4.2"],
    includes = [
        ".",
        "include",
        "util",
    ],
    local_defines = rocksdb_defines,
    visibility = ["//visibility:public"],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@oneTBB//:tbb",
    ],
)
