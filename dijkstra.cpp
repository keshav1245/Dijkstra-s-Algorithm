/* This file was first created on 4th April,2019 by Keshav Tangri
This is for educational purposes only.
This is for B.Tech Students who are or will be studying Data Structures in thier curriculum
For queries mail me @ : tangri57@gmail.com
*/
#include <iostream>

using namespace std;

class Node{
public:
Node * next;
int vertexName;
int distance;
int previousVertex;
};

class llist{
public:
Node * head = new Node;
llist(){
head = NULL;
}
Node * createnode(int vertexname,int distance,int previousvertex);
void addElement(int vertexname,int distance,int previousvertex);
void addatbeg(int vertexname,int distance,int previousvertex);
void deleteVertex(int pos);
int elementMinimum();
int searchele(int val);
void printingThePath(Node* vertex);
void display();
};

llist allVerticeLinkList,allDiscoveredVertices;

int main()
{

int v;
cout<<"Enter Number of vertices you have in your graph : ";
cin>>v;

int arr[v+1][v+1];
int j=0,i;
arr[0][0] = 0;
for(i=1;i<v+1;i++){
	arr[j][i] = i;
	arr[i][j] = i;
}

for(int i=1;i<v+1;i++){
for(int j=1;j<v+1;j++){
    if(i==j){
    arr[i][j] = 0;
    }else{
    cout<<"Enter weight of edge from "<<arr[i][0]<<" to "<<arr[0][j]<<" (if any) : ";
    cin>>arr[i][j];
    }
}
}
//PRINTING ADJACENCY MATRIX
cout<<"\n\nMATRIX IS : \n\n";
for(i=0;i<v+1;i++){
	for(j=0;j<v+1;j++){
		cout<<arr[i][j]<<"     ";
	}
cout<<"\n\n";
}

//SOURCE VERTEX INFO
int sourceVertex;
cout<<"Enter the source vertex from 1 to "<<v<<" : ";
cin>>sourceVertex;
while( !(sourceVertex>=1 && sourceVertex<=v) ){
cout<<"Source Vertex is Out of Range !\nEnter Again : ";
cin>>sourceVertex;
}
cout<<"\n\nSource Vertex is : "<<sourceVertex<<"\n\n";
//SOURCE VERTEX INFO ENDS


//DIJKSTRA'S ALGORITHM BEGIN !

//INITIALIZING THE LINK LIST HAVING ALL VERTICES AND SOURCE
//VERTEX INITIALIZED
for(int i=1;i<=v;i++){
if(i==sourceVertex)
allVerticeLinkList.addElement(i,0,NULL);
else
allVerticeLinkList.addElement(i,4294967294/2,NULL);
}

cout<<"\n\nPrinting the allVerticeLinkList Before deletion : \n\n";
allVerticeLinkList.display();
cout<<"\n\nPrinting the allDiscovered nodes LL Before deletion : \n\n";
allDiscoveredVertices.display();

while(allVerticeLinkList.head!=NULL){

//finding minimum value and adding the details to the discovered nodes list
int minimumValue = allVerticeLinkList.elementMinimum();
//Finding the position of the minimum value
int position_of_minimumValue = allVerticeLinkList.searchele(minimumValue);
//Deleting the vertex of miimum distance from all vertices list
//since it is already processed
allVerticeLinkList.deleteVertex(position_of_minimumValue);

//Next our goal will be relaxing an edge
Node * peakVertex = allDiscoveredVertices.head;

if(peakVertex==NULL){
break;
}else{
for(int i=1;i<=v;i++){
if(arr[peakVertex->vertexName][i] == 0){
continue;
}else{

Node* ptr = allVerticeLinkList.head;
while(ptr!=NULL){
if(ptr->vertexName==i && peakVertex->distance + arr[peakVertex->vertexName][i] < ptr->distance ){
ptr->distance = arr[peakVertex->vertexName][i] + peakVertex->distance;
ptr->previousVertex = peakVertex->vertexName;
break;
}
ptr =ptr->next;
}
}
}
}


}


for(int i=1;i<=v;i++){
Node * ptr = allDiscoveredVertices.head;
while(ptr->vertexName!=i){
ptr = ptr->next;
}
cout<<"\n Shortest Distance of vertex "<<i<<" is : "<<ptr->distance<<"\n";
cout<<"\n Path of the vertex "<<i<<" is : ";
allDiscoveredVertices.printingThePath(ptr);
cout<<" "<<i<<"\n";
}


    return 0;
}


//CREATING THE NODE !
Node* llist::createnode(int vertexname,int distance,int previousvertex){
    Node* temp =new Node;
    temp->vertexName = vertexname;
    temp->distance = distance;
    temp->previousVertex = previousvertex;
    return temp;
}
//ADDING ELEMENT IN THE LIST !
void llist::addElement(int vertexname,int distance,int previousvertex){

if(head == NULL){
    Node* temp = createnode(vertexname,distance,previousvertex);
    temp->next = head;
    head = temp;
}else{
    Node* temp = createnode(vertexname,distance,previousvertex);
    Node* ptr =head;
    while(ptr->next!=NULL){
    ptr=ptr->next;
    }
    temp->next=NULL;
    ptr->next=temp;
}
}
//ADD ELEMENT AT BEGINNING !
void llist::addatbeg(int vertexname,int distance,int previousvertex){
Node * temp = createnode(vertexname,distance,previousvertex);
temp->next = head;
head = temp;
}
//PRINTING THE LINKED LIST !
void llist::display(){
Node* ptr = head;
if(head==NULL){
cout<<"\n List does not Exist !\n";
return;
}
while(ptr!=NULL){
cout<<"Vertex Name : "<<ptr->vertexName<<endl;
cout<<"Vertex Distance : "<<ptr->distance<<endl;
cout<<"Vertex Previous Vertex : "<<ptr->previousVertex<<endl<<"\n";
ptr = ptr->next;
}
cout<<"\n\n";
}

//DELETE AT POSITION !
void llist::deleteVertex(int pos){
if(head == NULL){
return;
}
if(pos==1){
Node* p = head;
head = p->next;
delete p;
}else{
int counter = 0;
Node* p = head;
while(p!=NULL){
p=p->next;
counter++;
}
if(pos>1&&pos<=counter){
p = head;
Node* prev;
for(int i=1;i<pos;i++){
prev =p;
p=p->next;
}
prev->next=p->next;
delete p;
}else{
cout<<"\nOUT OF RANGE EXCEPTION !\n\n";
}
}
}
//VALUE OF MINIMUM ELEMENT

int llist::elementMinimum(){
Node * minptr = head;
Node * ptrnext = head->next;
int min = head->distance;
while(ptrnext!=NULL){
if(ptrnext->distance<min){
    min = ptrnext->distance;
    minptr = ptrnext;
}
    ptrnext = ptrnext->next;
}

allDiscoveredVertices.addatbeg(minptr->vertexName,minptr->distance,minptr->previousVertex);
return min;
}

//SEARCHING FOR POSITION OF MINIMUM ELEMENT

int llist::searchele(int val){
int counter=0;
Node* p = head;
if(head==NULL){
return counter;
}
while(p!=NULL){
counter++;
if(p->distance==val){
break;
}
p=p->next;
}
if(p==NULL){
counter = 0;
}
return counter;
}

//Printing the Node path and distance
void llist::printingThePath(Node* vertex){
if(vertex->previousVertex == 0){
return;
}else{
Node * ptr = head;
while(ptr->vertexName != vertex->previousVertex){
ptr = ptr->next;
}

printingThePath(ptr);
cout<<" "<<ptr->vertexName<<" -> ";
}

}

