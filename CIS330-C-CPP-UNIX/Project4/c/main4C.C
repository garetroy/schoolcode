#include <filters.h>
#include <cstdlib>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);
    int size = atoi(argv[3]);
    Color solidred(size,size,255,0,0);
    Color solidblue(size,size,0,0,255);
    Blender blend;
    blend.SetInput(solidred.GetOutput());
    blend.SetInput2(solidblue.GetOutput());

    blend.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(blend.GetOutput());
    writer.Write(argv[2]);

}