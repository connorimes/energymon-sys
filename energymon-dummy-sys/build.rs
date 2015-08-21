extern crate pkg_config;

use std::env;
use std::fs::{self, create_dir_all, remove_dir_all};
use std::path::PathBuf;
use std::process::Command;

fn main() {
    let pc = pkg_config::find_library("energymon-dummy-static");
    if pc.is_err() {
        let src = PathBuf::from(&env::var_os("CARGO_MANIFEST_DIR").unwrap())
                               .join("energymon");
        let dst = PathBuf::from(&env::var_os("OUT_DIR").unwrap());
        let _ = fs::create_dir(&dst);
        let build = src.join("_build");
        remove_dir_all(&build).ok();
        create_dir_all(&build).unwrap();
        run(Command::new("cmake").arg(src.to_str().unwrap()).current_dir(&build));
        run(Command::new("make").arg("energymon-dummy-static").current_dir(&build));
        println!("cargo:rustc-link-lib=static=energymon-dummy-static");
        println!("cargo:rustc-link-search=native={}", build.join("lib").display());
    }
}

fn run(cmd: &mut Command) {
    match cmd.status() {
        Ok(status) => assert!(status.success()),
        Err(e) => panic!("Unable to execute {:?}! {}", cmd, e),
    }
}
