/***************************************
*  vector可以理解成数组,只不过它还有扩充的功能
***************************************/

#include <vector>
#include <string>
#include <sstream>

int main()
{
    string aa[5];
	std::vector<std::string> imageName(aa,aa+5);
    std::vector<string>::iterator iter; //迭代器,本质是个指针
    for(int i=0;i<5;i++)
    {
        std::string tmpString;
        std::stringstream tmpStream;
        tmpStream<<(i+1);	//int转stringstream
        tmpStream>>tmpString; //stringstream转string
        aa[i]= tmpString.append(".png"); //n.png
    }
	for(iter=imageName.begin();iter!=imageName.end();iter++)//指针遍历速度快
    {
        std::cout<<*iter<<"  ";
    }
    return 0;
}
/**
*输出结果:
1.png  2.png  3.png  4.png  5.png
*/