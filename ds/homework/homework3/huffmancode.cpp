#include <iostream>
#include "../../Header/BinTree.h"
#include "../../Header/List.h"
#include "../../Header/Bitmap.h"
#include "../../Header/Hashtable.h"
using namespace std; 
struct HuffChar{
	char ch; int weight;
	HuffChar(char c = '^', int w = 0) : ch(c), weight( w ){};
	bool operator < (HuffChar const& hc) {return weight > hc.weight;
	}
	bool operator > (HuffChar const& hc) {return weight < hc.weight;
	}
	bool operator <= (HuffChar const& hc) {return weight >= hc.weight;
	}
	bool operator >= (HuffChar const& hc) {return weight <= hc.weight;
	}
	bool operator == ( HuffChar const& hc){return weight == hc.weight;
	}
	bool operator != ( HuffChar const& hc){return weight != hc.weight;
	}
};
#define N_CHAR (0x80 - 0x20)
#define HuffTree BinTree<HuffChar>


typedef List<HuffTree*> HuffForest;
typedef Bitmap HuffCode;
typedef Hashtable<char, char*> HuffTable;

//ͳ���ַ�����Ƶ��
int* statistics(char* sample_text_file) { 
	int* freq = new int[N_CHAR];  //����ͳ����������ʣ����������¼���ַ����ִ���
	memset(freq, 0, sizeof(int) * N_CHAR); //����
	FILE* fp = fopen(sample_text_file, "r"); //assert: �ļ������ҿ���ȷ��
	for (char ch; 0 < fscanf(fp, "%c", &ch); ) //���ɨ�������ļ��е�ÿ���ַ�
		if (ch >= 0x20) 
			freq[ch - 0x20]++; //�ۼƶ�Ӧ�ĳ��ִ���
	fclose(fp);
	return freq;
}
//����Ƶ����������Ƶ��ɭ�� 
HuffForest* initForest(int* freq)  
{
	HuffForest* forest = new HuffForest; //��Listʵ�ֵ�Huffmanɭ��
	for (int i = 0; i < N_CHAR; i++)   //Ϊÿ���ַ�
	{
		forest->insertAsLast(new HuffTree); //����һ�����������ַ�����Ƶ��
		forest->last()->data->insertAsRoot(HuffChar(0x20 + i, freq[i])); //��������
	}
	return forest;
}

HuffTree* minHChar( HuffForest* forest ){
	ListNodePosi(HuffTree*) p = forest->first();
	ListNodePosi(HuffTree*) minChar = p;
	int minWeight = p->data->root()->data.weight;
	while( forest->valid( p = p->succ ) )
		if(minWeight > p->data->root()->data.weight)
		{
			minWeight = p->data->root()->data.weight;
			minChar = p;
		}
	return forest->remove( minChar );
}
HuffTree* generateTree( HuffForest* forest )
{
	while( 1 < forest->size( ) )
	{
		HuffTree* T1 = minHChar( forest );
		HuffTree* T2 = minHChar( forest );
		HuffTree* S = new HuffTree();
		S->insertAsRoot( HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
		S->attachAsLC( S->root(), T1 );
		S->attachAsRC( S->root(), T2 );
		forest->insertAsLast( S );
		
	}
	return forest->first()->data;
}
//ͨ��������ȡ���ַ��ı���
static void generateCT(Bitmap* code, int length, HuffTable* table, BinNodePosi(HuffChar) v) {
	if (IsLeaf(*v)) //����Ҷ�ڵ㣨���ж��ַ��������жϣ�
	{
		table->put(v->data.ch, code->bits2string(length)); return;
	}
	if (HasLChild(*v)) //Left = 0
	{
		code->clear(length); generateCT(code, length + 1, table, v->lc);
	}
	if (HasRChild(*v)) //Right = 1
	{
		code->set(length); generateCT(code, length + 1, table, v->rc);
	}
}

//�����ַ�����ͳһ������ɢ�б�ʵ�ֵı������
HuffTable* generateTable(HuffTree* tree) { 
	HuffTable* table = new HuffTable; Bitmap* code = new Bitmap;
	generateCT(code, 0, table, tree->root()); 
	releases(code); 
	return table;
}; //release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ������ʵ����������

 //���ձ�����Bitmap������
int encode(HuffTable* table, Bitmap* codeString, char* s) {
	int n = 0; //�����صı��봮�ܳ�n
	for (size_t m = strlen(s), i = 0; i < m; i++) { //���������е�ÿ���ַ�
		char** pCharCode = table->get(s[i]); //ȡ�����Ӧ�ı��봮
		if (!pCharCode) pCharCode = table->get(s[i] + 'A' - 'a'); //Сд��ĸתΪ��д
		if (!pCharCode) pCharCode = table->get(' '); //�޷�ʶ����ַ�ͳһ�����ո�
		std::cout << *pCharCode;//printf("%s", *pCharCode); //�����ǰ�ַ��ı���
		for (size_t m = strlen(*pCharCode), j = 0; j < m; j++) //����ǰ�ַ��ı��������봮
			'1' == *(*pCharCode + j) ? codeString->set(n++) : codeString->clear(n++);
	}
	printf("\n"); return n;
} //�����Ʊ��봮��¼��λͼcodeString��
// ���ݱ������Գ�Ϊn��Bitmap����Huffman����
void decode(HuffTree* tree, Bitmap* code, int n) {
	BinNodePosi(HuffChar) x = tree->root();
	for (int i = 0; i < n; i++) {
		x = code->test(i) ? x->rc : x->lc;
		if (IsLeaf(*x)) { 
			std::cout << x->data.ch << " ";
			//printf("%c", x->data.ch); 
			x = tree->root();
		}
	}
	if (x != tree->root()) 
		std::cout << "...";//printf("...");
	std::cout << std::endl;// printf("\n");
} //��������룬�ڴ�ֱ�Ӵ�ӡ�����ʵ���пɸ�Ϊ������Ҫ�����ϲ������


int main(int argc, char* argv[]) { //Huffman�����㷨ͳһ����
    
    char text[] = "dream";
	char* ch = text;
	
	char text2[] = "apple";
	char* ch2 = text2;
 
    char s[] = "1.txt";
    char h[] = "../../data/test_1.txt";
    char t[] = "2.txt";

    int* freq = statistics(s); //���������ļ���ͳ�Ƹ��ַ��ĳ���Ƶ��
    HuffForest* forest = initForest(freq); //����Huffmanɭ��
    releases(freq); 
    HuffTree* tree = generateTree(forest);  //����Huffman������
    releases(forest);
    //print(tree); //���������
    
    HuffTable* table = generateTable(tree); //��Huffman������ת��Ϊ�����
    for (int i = 0; i < N_CHAR; i++) //��������
        printf(" %c: %s\n", i + 0x20, *(table->get(i + 0x20)));

    for (int i = 2; i < 3; i++) 
	{ //���������д����ÿһ���Ĵ�
        printf("\nEncoding : %s\n", ch); //���²��Ա���
        Bitmap* codeString = new Bitmap; //�����Ʊ��봮
        int n = encode(table, codeString, text); //�����ݱ�������ɣ�����Ϊn��
        //printf("%s\n", codeString->bits2string(n)); //����ñ��봮
        printf("Decoding: \n"); //���²��Խ���
        decode(tree, codeString, n); //����Huffman���������Գ���Ϊn�Ķ����Ʊ��봮����
        releases(codeString);
    }
    printf("\nEncoding : %s\n", ch2); //���²��Ա���
    Bitmap* codeString = new Bitmap; //�����Ʊ��봮
    int n = encode(table, codeString, text2); //�����ݱ�������ɣ�����Ϊn��
    //printf("%s\n", codeString->bits2string(n)); //����ñ��봮
    printf("Decoding: \n"); //���²��Խ���
    decode(tree, codeString, n); //����Huffman���������Գ���Ϊn�Ķ����Ʊ��봮����
    releases(codeString);
    
    system("pause");
    releases(table); 
    releases(tree);
    return 0; //�ͷű����������
}
