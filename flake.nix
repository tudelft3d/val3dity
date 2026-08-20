{
  description = "val3dity: validation of 3D primitives according to ISO 19107";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-26.05";
  };

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;

      packagesFor = system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        {
          val3dity = pkgs.stdenv.mkDerivation {
            pname = "val3dity";
            version = "2.6.0";
            src = self;

            nativeBuildInputs = with pkgs; [
              cmake
              ninja
            ];

            buildInputs = with pkgs; [
              cgal
              gmp
              mpfr
              eigen
              geos
              spdlog
              pugixml
              tclap
              boost
              nlohmann_json
            ];

            cmakeFlags = [
              "-DVAL3DITY_USE_INTERNAL_DEPS=OFF"
              "-G Ninja"
            ];

            meta = with pkgs.lib; {
              description = "Validation of 3D primitives according to ISO 19107";
              homepage = "https://github.com/tudelft3d/val3dity";
              license = licenses.gpl3Only;
              mainProgram = "val3dity";
              platforms = platforms.all;
            };
          };
        };
    in
    {
      packages = forAllSystems (system:
        let
          packages = packagesFor system;
        in
        packages // {
          default = packages.val3dity;
        }
      );
    };
}
