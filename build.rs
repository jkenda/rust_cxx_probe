fn main() {
    cxx_build::bridge("src/main.rs")
        .file("src/blobstore.cpp")
        .std("c++20")
        .compile("rust_cxx_probe");

    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=src/blobstore.cc");
    println!("cargo:rerun-if-changed=include/blobstore.h");
}
