#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
    fstream fout("grid.dae", fstream::out);

    double w = ::atof(argv[1]);
    double h = ::atof(argv[2]);

    fout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\">\n";
    fout << "<COLLADA xmlns=\"http://www.collada.org/2005/11/COLLADASchema\" version=\"1.4.1\">\n";
    fout << "  <asset>\n";
    fout << "    <up_axis>Z_UP</up_axis>\n";
    fout << "  </asset>\n";
    fout << "  <library_geometries>\n";
    fout << "    <geometry id=\"grid\">\n";
    fout << "      <mesh>\n";
    fout << "        <source id=\"vectors\">\n";
    fout << "          <float_array id=\"vector_coords\" count=\"60\"\n";
    fout << "            " << w << " " << h << " " << 0.00 << "\n";
    fout << "            " << 0 << " " << 0 << " " << 0.00 << "\n";
    fout << "            " << 0 << " " << h << " " << 0.00 << "\n";
    fout << "            " << w << " " << 0 << " " << 0.00 << "\n";
    fout << "            " << 0 << " " << h << " " << 0.01 << "\n";
    fout << "            " << w << " " << h << " " << 0.00 << "\n";
    fout << "            " << 0 << " " << h << " " << 0.00 << "\n";
    fout << "            " << w << " " << h << " " << 0.01 << "\n";
    fout << "            " << w << " " << h << " " << 0.00 << "\n";
    fout << "            " << w << " " << 0 << " " << 0.01 << "\n";
    fout << "            " << w << " " << 0 << " " << 0.00 << "\n";
    fout << "            " << w << " " << h << " " << 0.01 << "\n";
    fout << "            " << w << " " << 0 << " " << 0.01 << "\n";
    fout << "            " << 0 << " " << 0 << " " << 0.00 << "\n";
    fout << "            " << w << " " << 0 << " " << 0.00 << "\n";
    fout << "            " << 0 << " " << 0 << " " << 0.01 << "\n";
    fout << "            " << 0 << " " << h << " " << 0.01 << "\n";
    fout << "            " << 0 << " " << 0 << " " << 0.00 << "\n";
    fout << "            " << 0 << " " << 0 << " " << 0.01 << "\n";
    fout << "            " << 0 << " " << h << " " << 0.00 << "\n";
    fout << "          </float_array>\n";
    fout << "          <technique_common>\n";
    fout << "            <accessor count=\"20\" source=\"#vector_coords\" stride=\"3\">\n";
    fout << "              <param name=\"X\" type=\"float\" />\n";
    fout << "              <param name=\"Y\" type=\"float\" />\n";
    fout << "              <param name=\"Z\" type=\"float\" />\n";
    fout << "            </accessor>\n";
    fout << "          </technique_common>\n";
    fout << "        </source>\n";

    return 0;
}
