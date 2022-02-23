class UnionFind {
 public:
  UnionFind();
  UnionFind(UnionFind&&) = default;
  UnionFind(const UnionFind&) = default;
  UnionFind& operator=(UnionFind&&) = default;
  UnionFind& operator=(const UnionFind&) = default;
  ~UnionFind();

  void union(int p, int q);

  void connetted(int p, int q);

 private:
};

UnionFind::UnionFind() {}

UnionFind::~UnionFind() {}