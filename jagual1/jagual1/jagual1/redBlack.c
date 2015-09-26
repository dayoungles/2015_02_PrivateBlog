//
//  redBlack.c
//  jagual1
//
//  Created by Dayoungle on 2015. 1. 4..
//  Copyright (c) 2015년 dayoungle. All rights reserved.
//

#include <stdio.h>
typedef struct node node_t;
typedef struct tree tree_t;
void insertionFix(tree_t* tree, node_t* insertNode);
void leftRotate(tree_t* tree, node_t* target);
void rightRotate(tree_t* tree, node_t* target);
void insertion(tree_t* tree, node_t* newNode);
void deleteFixup(tree_t* tree, node_t* fixupNode);
/*
    트리의 각 노드가 가지고 있는 구조
 */
struct node {
    node_t* parent;
    int color;//black 0, red 1;
    node_t* left;
    node_t* right;
    int data;
};

/*
    트리가 가지고 있어야 하는 구조
 */
struct tree{
    node_t* root;
    node_t* left;
    node_t* right;
};

/*
    주어진 타겟을 기준으로 좌 로테이션.
    ** target인자가 돌리려고 하는 서브 트리의 차일드가 아니라 서브트리의 루트.
 */
 
void leftRotate(tree_t* tree, node_t* target){
    node_t* sub;
    if(target == tree->root) return;
    if(!target) return;
    
    sub = target->right;
    target-> left = sub ->right;
    if(sub->right != NULL){
        sub->right->parent = target->left;
    }
    if(target->parent == NULL){
        tree -> root = sub;
    } else if(target->parent ->left == target){
        target->parent->left = sub;
    } else {
        target->parent -> right = sub;
    }
    sub->parent = target->parent;
    
    sub->left = target;
    target->parent = sub;
   
}

/*
    주어진 타겟을 기준으로 우 로테이션
 */
void rightRotate(tree_t* tree, node_t* target){
    node_t* sub;
    if(target == tree->root) return;
    if(!target || !tree) return;
    
    sub = target->left;
    target->left = sub->right;
    if(sub->right != NULL){
        sub->right -> parent = target->left;
    }
    
    if(target->parent == NULL){
        tree->root = sub;
    } else if(target -> parent -> left == target){
        target->parent-> left = sub;
    } else {
        target -> parent -> right = sub;
    }
    sub -> parent = target -> parent;
    
    target-> parent = sub;
    sub ->right = target;
}

/*
    새로운 노드를 인설션. BST코드와 크게 다르지 않으나 insertion fix함수로 RB트리 위배내용을 확인해줘야 함.
 */
void insertion(tree_t* tree, node_t* newNode){
    if(!tree || !newNode) return;
    newNode -> color = 1;//red로 설정.
    node_t* temp = tree-> root;
    node_t* parent = (node_t*)NULL;
    while(temp != NULL){
        parent = temp;
        if(temp->data < newNode-> data){
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    newNode-> parent = parent;
    if(parent == NULL){
        tree->root = newNode;
    } else if(parent-> data < newNode->data){
        parent->left = newNode;
    } else {
        parent -> right = newNode;
    }
    newNode->left = NULL;
    newNode-> right = NULL;
    
    insertionFix(tree, newNode);
    
}

/*
    인설션 시 룰 위배 내용 수정하는 함수. 
 */
void insertionFix(tree_t* tree, node_t* insertNode){
    node_t* uncle = (node_t*) NULL;
    //이미 insertion에서 제대로 들어온 값인지 확인했기 때문에 널값 확인 안함.
    //삽입된 노드가 루트일 경우 블랙으로 변경.
    if(tree->root == insertNode){
        insertNode->color = 0;
        return;
    }
    
    while(insertNode->parent->color == 1){
        //insertnode의 부모노드가 좌일경우
        if(insertNode->parent == insertNode->parent->parent->left){
            uncle = insertNode->parent->parent->right;
            //삼촌이 레드면
            if(uncle->color==1){
                //삼촌과 부모의 색을 블랙으로 하고,
                uncle-> color = 0;
                insertNode->parent ->color = 0;
                //할아버지의 색을 레드로.
                insertNode->parent->parent->color = 1;
                //인서트 노드를 할배노드로 변경.
                insertNode = insertNode->parent->parent;
            } else {
            //삼촌이 블랙이면
                //나의 위치가 우일경우
                if(insertNode == insertNode->parent->right){
                    //좌로테이션하고
                    leftRotate(tree, insertNode->parent);
                    //insertnode를 부모로 변경.
                    insertNode = insertNode->parent;
                }
                //부모의 부모노드를 레드로.
                insertNode->parent->parent ->color = 1;
                //부모 노드를 블랙으로.
                insertNode->parent ->color = 0;
                //부모의 부모노드를 기준으로 우로테이션
                rightRotate(tree, insertNode->parent->parent);
            }
        } else {
        //insertnode의 부모가 우일경우 반대로 한다.
            uncle = insertNode->parent->parent->left;
            if(uncle->color==1){
                //삼촌과 부모의 색을 블랙으로 하고,
                uncle-> color = 0;
                insertNode->parent ->color = 0;
                //할아버지의 색을 레드로.
                insertNode->parent->parent->color = 1;
                //인서트 노드를 할배노드로 변경.
                insertNode = insertNode->parent->parent;
            } else {
                //삼촌이 블랙이면
                //나의 위치가 좌일경우
                if(insertNode == insertNode->parent->left){
                    //우 로테이션하고
                    rightRotate(tree, insertNode->parent);
                    //insertnode를 부모로 변경.
                    insertNode = insertNode->parent;
                }
                //부모의 부모노드를 레드로.
                insertNode->parent->parent ->color = 1;
                //부모 노드를 블랙으로.
                insertNode->parent ->color = 0;
                //부모의 부모노드를 기준으로 우로테이션
                leftRotate(tree, insertNode->parent->parent);
            }
        }
    }
    tree->root->color = 0;
}

/*
    삭제할 노드와 삭제한 곳에 삽입할 노드. 
    BST와 다른 점은 삽입할 때 삭제할 노드의 색상을 넣어줘야 한다는 것.
 */
void transplant(tree_t* tree, node_t* target, node_t* alter){
    if(!target || !alter) return;//어떻게 에러 처리를 해준담.
    
    //타겟이 루트이면 트리의 루트로 알터를 설정.
    if(target->parent == NULL){
        tree->root = alter;
    } else if(target->parent->left == target){//타겟이 부모의 왼쪽 차일드면 타겟 부모의 왼쪽에 알터 삽입
        target->parent->left = alter;
    } else {
        target->parent->right = alter; //타겟이 부모의 오른쪽 차일드면 타겟 부모의 오른쪽에 알터 삽입.
    }
    alter->parent = target->parent;//알터의 부모를 타겟의 부모로 설정.
    alter->color = target->color;//알터의 색상을 타겟의 색상으로 설정.

    return;
}

/*
    주어진 노드를 루트로 하는 서브트리에서 최소값을 찾는 함수.
    return node;
 */
node_t * findMin(node_t* node){
    if(!node) return node;// NIL일 경우?
    
    while(node->left){
        node = node -> left;
    }
    return node;
}

/*
    노드를 삭제하는 함.수.
 */
void deletion(tree_t* tree, node_t* node){
    int originalColor = node-> color;
    node_t* successor = (node_t*) NULL;
    node_t* fixupNode = (node_t*)NULL;
    
    //노드의 왼쪽 차일드가 없을 경우 && 노드가 하나도 없을 때는 여기서 처리됨
    if(node->left == NULL){
        fixupNode = node->right;
        transplant(tree, node, node->right);
    } else if(node->right == NULL){ //노드의 오른쪽 차일드가 없을 경우
        fixupNode = node -> left;
        transplant(tree, node, node->left);
    } else {
        //노드의 차일드가 두개일 경우.
        successor = findMin(node->right);
        fixupNode = successor->right;
        originalColor = successor -> color;
        //만약 석세서의 부모가 삭제하려는 노드일 경우.
        if(successor->parent == node){
            fixupNode ->parent = successor;
        }else {
            transplant(tree, successor, successor->right);
            successor->right = node->right;
            successor->right-> parent = successor;
        }
        //노드 삭제 처리.
        transplant(tree, node, successor);
        successor->left = node->left;
        successor->left -> parent = successor;
        successor->color = node->color;
        
    }
    
    if(originalColor == 0){
        deleteFixup(tree, fixupNode);
    }
}

void deleteFixup(tree_t* tree, node_t* fixupNode){
    node_t* sibling = (node_t*)NULL;
    
    while(fixupNode != tree->root && fixupNode->color == 0){
        if(fixupNode == fixupNode->left){
            sibling= fixupNode->parent->right;
            //만약 형제가 레드이면,
            if(sibling->color == 1){
            //시블링은 블랙블랙이다. 확인? 필요없을 듯. 블랙블랙이 안되면 알비 트리가 안됨.
            //시블링을 블랙
            //부모를 레드로 변경.
            //부모를 인자로 해서 좌로테이션.
            //fixupNode는 그대로 두고 종료하면 와일문에서 계속 돈다.
            }else {
                //만약 시블링 오른쪽 차일드가 레드이면
                //오른쪽 차일드는 블랙으로 변경
                //시블링은 부모 색깔로 변경
                //부모는 블랙으로 변경
                //좌로테이션
                
                //else
                //시블링의 왼쪽 자식이 블랙이면
                    //부모의 색을 레드로 바꾸고
                    //fixupNode = parent로 바꿔서 다시 블랙 하이트을 확인하도록 한다.
                //시블링의 왼쪽자식이 레드이면
                    //시블링의 왼쪽자식을 블랙으로 변경
                    //시블링을 레드
                    //시블링을 인자로, 우 로테이션
                    //종료하면 와일문에서 다시 확인해서 처리한다.
            }
        } else {
            
        }

        
    }
}























































