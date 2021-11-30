#include <zk/client.hpp>
#include <zk/multi.hpp>
#include <zk/server/configuration.hpp>
#include <zk/server/server.hpp>

#include <exception>
#include <iostream>

/** All result types are printable for debugging purposes. **/
template <typename T>
void print_thing(const zk::future<T>& result)
{
    try
    {
        // Unwrap the future value, which will not block (based on usage), but could throw.
        T value(result.get());
        std::cerr << value << std::endl;
    }
    catch (const std::exception& ex)
    {
        // Error "handling"
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
}

int main()
{
    // Start a ZK server running on localhost (not needed if you just want a client, but great for testing and
    // demonstration purposes).
    zk::server::server server(zk::server::configuration::make_minimal("zk-data", 2181));

    // zk::client::connect returns a future<zk::client>, which is delivered when the connection is established.
    auto client = zk::client::connect("zk://127.0.0.1:2181")
                             .get();

    // get_result has a zk::buffer and zk::stat.
    client.get("/foo/bar")
        .then(print_thing<zk::get_result>);

    // get_children_result has a std::vector<std::string> for the path names and zk::stat for the parent stat.
    client.get_children("/foo")
        .then(print_thing<zk::get_children_result>);

    // set_result has a zk::stat for the modified ZNode.
    client.set("/foo/bar", "some data")
        .then(print_thing<zk::set_result>);

    // More explicit: client.create("/foo/baz", "more data", zk::acls::open_unsafe(), zk::create_mode::normal);
    client.create("/foo/baz", "more data")
        .then(print_thing<zk::create_result>);

    client.get("/foo/bar")
        .then([client] (const auto& get_res)
        {
            zk::version foo_bar_version = get_res.get().stat().data_version;

            zk::multi_op txn =
            {
                zk::op::check("/foo", zk::version::any()),
                zk::op::check("/foo/baz", foo_bar_version),
                zk::op::create("/foo/bap", "hi", nullopt, zk::create_mode::sequential),
                zk::op::erase("/foo/bzr"),
            };

            // multi_res's type is zk::future<zk::multi_result>
            client.commit(txn).then(print_thing<zk::multi_result>);
        });

    // This is not strictly needed -- a client falling out of scope will auto-trigger close
    client.close();
}
