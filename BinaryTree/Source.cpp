#include<iostream>
#include<istream> 
#include<fstream>

using namespace std;



struct Tree
{
	int index;
	Tree* left;
	Tree* right;
};
Tree* tree = NULL;

int height = 0;

//вставка листа
bool push(Tree **node, int newIndex )
{	
	if ((*node) == NULL) //Если дерева не существует                  
	{
		(*node) = new Tree;                
		(*node)->index = newIndex;                 
		(*node)->left = (*node)->right = NULL;       
		return true;                       
	}
	
	if (newIndex > (*node)->index) {//Дерево есть
		push(&(*node)->right, newIndex);
	}
	else if (newIndex < (*node)->index) {
		push( &(*node)->left, newIndex);
	}
	else return false;
}

//исключение
Tree* pop(struct Tree *node, int key) {

	struct Tree *tempLeft, *tempRight;
	if (!node) return node; //ключ не найден

	if (node->index == key) {  //удаление узла
		
							   
		if (node->left == node->right) {//если нет потомков
			free(node);
			return NULL;
		}

		else if (node->left == NULL) {  //если есть только правый потомок
			tempRight = node->right;
			free(node);
			return tempRight;
		}

		else if (node->right == NULL) { //если есть только левый потомок
			tempLeft = node->left;
			free(node);
			return tempLeft;
		}

		else {//если есть оба потомока
			
			tempRight = node->right;
			tempLeft = node->right;
			while (tempLeft->left)  tempLeft = tempLeft->left;
			tempLeft->left = node->left;
			free(node);

			return tempRight;
		}
	}

	if (node->index < key) {
		node->right = pop(node->right, key);
	}
	else {
		node->left = pop(node->left, key);
	}
	return node;
}

//отображение дерева 
void print(Tree *t, int u=0)
{
	if (t == NULL) return;              
	else
	{
		print(t->left, ++u);                   //С помощью рекурсивного посещаем левое поддерево
		for (int i = 0; i < u; ++i) cout << "|";
		cout << t->index << endl;           
		u--;
	}
	print(t->right, ++u);                       //С помощью рекурсии посещаем правое поддерево
}

//поиск листа
Tree* find(Tree* node, int numberOffind,int k=0) {
	
	if (node == NULL) {
		return NULL;
	}
	
	find(node->left, numberOffind,k);
		
	cout << node->index << endl;
	if (k==numberOffind) {
	return node;
	}else k++;
		
	find(node->right, numberOffind,k);
	
}

//высота дерева
int heightOfTree(Tree* node) {
	
	if (node == NULL) return 0;
	
	int left, right;
	
	if (node->left != NULL) {
		left = heightOfTree(node->left);
	}
	else left = -1;
	if (node->right != NULL) {
		right = heightOfTree(node->right);
	} 
	else right = -1;

	int max = left > right ? left : right;

	return max + 1;
}


//-поиск вершин, у которых количество потомков в левом поддереве отличается
// от количества потомков в правом поддереве на единицу, на основе рекурсивного 
// алгоритма восходящего обхода;
//количество потомков
int numberOfChildren(Tree* node) {

	if (node->left == NULL && node->right == NULL) return 1;

	int left, right;

	if (node->left != NULL) left = numberOfChildren(node->left);
	else left = 0;
	
	if (node->right != NULL) right = numberOfChildren(node->right);
	else right = 0;

	if ((left - right) == 1  ) {
		cout << "Elem: "<< node->index << endl;
		left += right;
		right = 0;
	}

	return left + right + 1;
}

int main() {

	cout << "1. Find sheets with different number of children in left subtree and in the right subtree" << endl
		<< "2. Height of tree" << endl
		<< "3. Find k-word" << endl
		<< "4. Delete a elem by key" << endl
		<< "5. Exit" << endl;
	
	int task;

	/*заполнение дерева*/
	int c;
	fstream fileOut;
	fileOut.open("text.txt", ios::in);
	
	if (fileOut.is_open())
	{
		while (fileOut >> c)
		{
			if (!push(&tree, c)) cout << "Not Ok" << endl;
		}
	}

	print(tree);
	cout << "Write number of task: ";
	std::cin >> task;

	while (task != 5) {
		switch (task)
		{

		case 1:
			numberOfChildren(tree);
			break;

		case 2:
			cout << "Height of tree: " << heightOfTree(tree) << endl;
			break;

		case 3: {
			cout << "Write k for find: " ;
			int findIndex;
			std::cin >> findIndex;
			Tree* ftree = (struct Tree*)malloc(sizeof(struct Tree));
			ftree=find(tree, findIndex);
			if(ftree!=NULL) cout << "k-index for find: " << ftree->index << endl;
			}
			break;

		case 4: {
			int elemOfDelete;
			cout << "Write index for delete: ";
			std::cin >> elemOfDelete;
			tree = pop(tree, elemOfDelete);
			cout << "\tTree\n";
			print(tree);
			}
			break;

		default:
			cout << "Wrong numder. Try again." << endl ;
			break;

		}

		cout << "Write number of task: ";
		std::cin >> task;
	}


	free(tree);
	return 0;
}