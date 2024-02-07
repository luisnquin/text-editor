{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = inputs:
    with inputs;
      flake-utils.lib.eachDefaultSystem (
        system: let
          pkgs = import nixpkgs {
            config = {
              allowBroken = false;
              allowUnfree = true;
            };
            inherit system;
          };
        in {
          defaultPackage = pkgs.hello;

          devShells.default = pkgs.mkShell {
            inherit system;

            buildInputs = with pkgs; [
              ncurses
              just
              gcc
            ];
          };
        }
      );
}
