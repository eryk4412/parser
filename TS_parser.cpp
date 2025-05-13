#include "tsCommon.h"
#include "tsTransportStream.h"

//=============================================================================================================================================================================

int main(int argc, char *argv[ ], char *envp[ ])
{
  // TODO - open file
  //if (argc < 2){
    //printf("Brak pliku wejściowego!\n");
    //return EXIT_FAILURE;

  //}
  // TODO - check if file if opened
  FILE *file = fopen(argv[1], "rb");
  if(!file){
    printf("Nie udało się otworzyć pliku\n");
    return EXIT_FAILURE;
  }

  xTS_PacketHeader    TS_PacketHeader;

  int32_t TS_PacketId = 0;
  uint8_t TS_PacketBuffer[188];
  while(!feof(file))
  {
    // TODO - read from file
    size_t bytesRead = fread(TS_PacketBuffer, 1, sizeof(TS_PacketBuffer), file);

    if (bytesRead == sizeof(TS_PacketBuffer)) {
      TS_PacketHeader.Reset();
      TS_PacketHeader.Parse(TS_PacketBuffer);

      printf("%010d ", TS_PacketId);
      TS_PacketHeader.Print();
      printf("\n");

      TS_PacketId++;
    }
  }
  
  // TODO - close file
  fclose(file); 

  return EXIT_SUCCESS;
}

//=============================================================================================================================================================================
