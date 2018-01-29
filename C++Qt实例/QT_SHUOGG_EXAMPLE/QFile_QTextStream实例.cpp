//rrrr.txt文件放在根目录的mytxt文件夹中,内容为shuogggggggggg
#include <qdebug.h>
#include <qfile.h>
#include <qtextstream.h>

int main(int argc, char *argv[])
{
    int i=1;
    std::stringstream strStream;
    std::vector<std::string> ivector;
    QString qwe;
    QFile file("mytxt/rrrr.txt"); //路径也可以"./mytxt/rrrr.txt"
    if(file.open(QFile::ReadOnly))
    {
        QTextStream str1(&file);
        qwe=str1.read(file.size());
    }
    else
        file.close();
    qDebug()<<qwe; //执行输出:shuogggggggggg
}

/****************************************************************/
//上面是读的,下面这个是写入的:
    if(file.open(QFile::WriteOnly))
    {
        QTextStream str1(&file);
        str1<<"aaaaaaaaaaaa";
    }
	else
        file.close();
//最后rrrr.txt文件里面内容会被aaaaaaaaaaa所覆盖
