struct ReqItem {
    1: string id,
    2: list<i64> fids,
}
struct Model {
    1: string name,
    2: bool use_multi,
    3: list<string> tags,
}

struct PredictReq {
    1: list<ReqItem> req_items,
    2: list<Model> models,
    3: i16 handle_nums
}

struct ResItem {
    1: string id,
    2: map<string, list<double>> tag_scores,  //得分
}

struct PredictRes {
    1: map<string, ResItem> res_items,
}

service GalaxyPredict{
    PredictRes predict(1: PredictReq req);
}
