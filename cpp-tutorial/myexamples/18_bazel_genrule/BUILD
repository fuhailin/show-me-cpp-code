genrule(
  name = "copy_of_main",
  srcs = ["main.c"],
  outs = ["copy_of_main.c"],
  cmd = "cp $< $@",
)

genrule(
  name = "renamed_main",
  srcs = ["copy_of_main.c"],
  outs = ["renamed_main.c"],
  tools = ["substitute.sh"],
  cmd = "$(location substitute.sh) 'Blaze' 'Bazel' $< $@",
)

cc_binary(
  name = "hello_bazel",
  srcs = [":renamed_main"],
)