"""Provides a macro to import all dependencies.

Some of the external dependencies need to be initialized. To do this, duplicate
the initialization code from WORKSPACE file.
"""

def mydeps_workspace():
    """All external dependencies."""

    # pass
    native.local_repository(
        name = "cppbuilt_lib",
        path = "/root/projects/cppbuilt_lib",
    )
    # git_repository(
    #     name = "cpp3rd_lib",
    #     commit = "10cec0e759d8048295e3fef6b32273bd455542e7",
    #     remote = "https://gitee.com/fuhailin/cpp3rd_lib.git",
    # )
