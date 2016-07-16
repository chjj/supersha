{
  "targets": [{
    "target_name": "supersha",
    "sources": [
      "./src/supersha.cc"
    ],
    "cflags": [
      "-Wall",
      "-Wno-maybe-uninitialized",
      "-Wno-uninitialized",
      "-Wno-unused-function",
      "-Wextra"
    ],
    "cflags_cc+": [
      "-std=c++0x"
    ],
    "include_dirs": [
      "/usr/local/include",
      "<!(node -e \"require('nan')\")"
    ],
  }]
}
