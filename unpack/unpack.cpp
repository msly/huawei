#include <iostream>
#include <fstream>

using namespace std;

struct IMG_STRUCT{
    char sign[4];
    int headSize;
    char unKnow[4];
    char hardwareId[8];
    unsigned int sequence;
    unsigned int fileSize;
    char fileDate[16];
    char fileTime[16];
    char fileName[32];
    char headChecksum[2];
};

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "usage:\ncd dload\nunpack UPDATE.APP" << endl;
        return 0;
    }

    cout << "please wait for unpacked" << endl;

    ifstream fin(argv[1], ios::binary|ios::in);
    if (fin) {

        // get total lenth
        fin.seekg(0, ios::end);
        size_t len = (size_t)fin.tellg();

        // find begin sign
        unsigned char beginSign[4] ={ 0x55, 0xaa, 0x5a, 0xa5 };
        fin.seekg(0, ios::beg);
        unsigned char sign[4] ={ 0 };
        while (fin.tellg() < len) {
            
            fin.read((char *)sign, 4);
            
            if (memcmp(beginSign, sign, 4) == 0) {
                fin.seekg(-4, ios::cur);


                IMG_STRUCT img;
                fin.read((char*)&img, sizeof(img));
                cout << "name:" << img.fileName 
                    << " headsize:" << img.headSize
                    << " filesize:" << img.fileSize 
                    << " date:" << img.fileDate
                    << " time:" << img.fileTime
                    << endl;

                // skin head
                fin.seekg(img.headSize - sizeof(img), ios::cur);

                // save file
                const int BUF_SIZE = 1024 * 100; // 100k
                char buf[BUF_SIZE];
                ofstream fout("./" + string(img.fileName) + ".img", ios::out|ios::binary);

                unsigned int isRead = 0;
                while (img.fileSize > isRead) {

                    int curRead = (img.fileSize - isRead <= BUF_SIZE) ? (img.fileSize - isRead) : BUF_SIZE;
                    fin.read(buf, curRead);
                    fout.write(buf, curRead);

                    isRead += curRead;
                }
                
                fout.close();

            } else {

                fin.seekg(-3, ios::cur);
            } 
        }
    }

    cout << "unpacked ... " << endl;
    getchar();
    return 0;
}
