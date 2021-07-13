#include <google/protobuf/stubs/common.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "lib/example.pb.h"
#include "lib/feature.pb.h"
#include "stringutils.cpp"
// #include "tensorflow/core/lib/core/stringpiece.h"
#include "tensorflow/core/lib/io/record_writer.h"

using namespace tensorflow::io;
using namespace tensorflow;
using namespace std;

bool int64_feature(Feature& feature, int value) {
    Int64List* i_list1 = feature.mutable_int64_list();
    i_list1->add_value(value);
    return true;
}
bool int64_feature(Feature& feature, std::vector<int> value) {
    if (value.size() < 1) {
        printf("value int64 is wrong!!!");
        return false;
    }
    Int64List* i_list1 = feature.mutable_int64_list();
    for (size_t i = 0; i < value.size(); ++i) i_list1->add_value(value[i]);
    return true;
}

void filetotfrecord(const string inputpath, const string outputpath, string output_name, map<string, int>& mapinput, map<string, int>& mapoutput) {
    ifstream read(inputpath);

    int max = 10000000;
    int count = 0;
    int fidx = 0;
    int64 line_id = 0;

    if (read.is_open()) {
        cout << "文件输入路径已经打开" << endl;
    } else {
        cout << "文件输入路径有误" << endl;
        return;
    }
    std::unique_ptr<WritableFile> file;

    RecordWriterOptions options = RecordWriterOptions::CreateRecordWriterOptions("NONE");

    RecordWriter* writer = NULL;

    vector<string> inputvec;
    std::string line;
    while (getline(read, line)) {
        inputvec.clear();
        split(inputvec, line, "\t");
        if (inputvec.size() == 2) {
            string nerinputstring = inputvec[0];
            string neroutstring = inputvec[1];
            vector<string> nerinputvec;
            vector<string> neroutputvec;
            nerinputvec.clear();
            neroutputvec.clear();

            split(nerinputvec, nerinputstring, "|");
            split(neroutputvec, neroutstring, "|");

            if (nerinputvec.size() == neroutputvec.size()) {
                if (line_id == 0 || count > max) {
                    if (writer != NULL) {
                        writer->Close();
                    }
                    char output_file[1024];
                    memset(output_file, 0, 1024);

                    sprintf(output_file, "%s/%s_%03d.tfrecord", outputpath.c_str(), output_name.c_str(), fidx);
                    printf("create new tfrecord file: [%s] \n", output_file);

                    Status s = Env::Default()->NewWritableFile((string)output_file, &file);
                    if (!s.ok()) {
                        printf("create write record file [%s] wrong!!!\n", output_file);
                        return;
                    }

                    writer = new RecordWriter(file.get(), options);
                    count = 0;
                    fidx += 1;
                }
                int len = nerinputvec.size() > 80 ? 80 : nerinputvec.size();

                Example example;
                Features* features = example.mutable_features();
                ::google::protobuf::Map<string, Feature>* feature = features->mutable_feature();
                Feature feature_tmp;

                vector<int> vecinputlast(80, 0);   //初始化了80个值为0的元素
                vector<int> vecoutputlast(80, 8);  //初始化了80个值为8的元素

                for (size_t i = 0; i < len; ++i) {
                    string e = nerinputvec[i];
                    if (e == " ") {
                        vecinputlast[i] = mapinput["blank"];
                    } else {
                        if (mapinput.count(e) > 0) {
                            vecinputlast[i] = mapinput[e];
                        } else {
                            vecinputlast[i] = mapinput["unknow"];
                        }
                    }
                }
                feature_tmp.Clear();

                if (!int64_feature(feature_tmp, vecinputlast)) {
                    printf(" vec : [%s]'s input wrong\n", vecinputlast.size());
                    return;
                }

                (*feature)["input"] = feature_tmp;

                feature_tmp.Clear();
                for (size_t j = 0; j < len; ++j) {
                    string e = neroutputvec[j];
                    if (mapoutput.count(e) > 0) {
                        vecoutputlast[j] = mapoutput[e];
                    } else {
                        vecoutputlast[j] = mapoutput[e];
                    }
                }

                if (!int64_feature(feature_tmp, vecoutputlast)) {
                    printf(" vecoutputlast : [%s]'s label wrong\n", vecoutputlast.size());
                    return;
                }
                (*feature)["label"] = feature_tmp;

                feature_tmp.Clear();
                std::string str;
                example.SerializeToString(&str);
                writer->WriteRecord(str);

                vecinputlast.clear();
                vecoutputlast.clear();
                ++count;

                if (line_id % 5000000 == 0 && line_id > 0) {
                    printf("Processed %s files.\n", line_id);
                }
            }
        }
        line_id++;
    }

    if (writer != NULL) {
        writer->Close();
    }
    read.close();
}

int main() {
    string mapinputpath = "/Users/vincent/Documents/projects/DeePray/examples/criteo/data/train.csv";
    string mapoutpath = "output.pd";
    map<string, int> mapinput;
    map<string, int> mapoutput;
    filereadtomap(mapinputpath, mapinput);
    filereadtomap(mapoutpath, mapoutput);

    string inputpath = "/Users/zhoumeixu/Desktop/all.txt";
    string outputpath = "/Users/zhoumeixu/Desktop/ner";
    string output_name = "ner";

    filetotfrecord(inputpath, outputpath, output_name, mapinput, mapoutput);

    return 0;
}