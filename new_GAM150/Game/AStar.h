#pragma once
/*
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

const int ROW = 6;
const int COL = 6;

struct Node {
    int row;
    int col;
    int g;
    int h;
    int f;
    Node* parent;
};

bool visited[ROW][COL];

// 비교 함수
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

// 예측 거리
int heuristic(int row, int col, int end_row, int end_col) {
    return abs(end_row - row) + abs(end_col - col);
}

// 경로 출력
void print_path(Node* current) {
    std::vector<Node*> path;
    while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
    }
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << "(" << path[i]->row << ", " << path[i]->col << ") ";
    }
    std::cout << std::endl;
}

std::vector<Node*> A_star(int map[ROW][COL], Node start_node, Node end_node) {
    // 우선순위 큐 생성
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    // 시작 노드를 큐에 넣음
    pq.push(&start_node);

    while (!pq.empty()) {
        // 현재 노드 선택
        Node* current = pq.top();
        pq.pop();

        // 목적지에 도달한 경우
        if (current->row == end_node.row && current->col == end_node.col) {
            print_path(current);
            std::vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            return path;
        }

        // 현재 노드를 방문한 적이 있는 경우
        if (visited[current->row][current->col]) {
            continue;
        }
        visited[current->row][current->col] = true;

        // 인접한 노드 탐색
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                // 대각선 방향은 이동할 수 없음
                if (i == 0 && j == 0 || std::abs(i) + std::abs(j) == 2) {
                    continue;
                }
                int new_row = current->row + i;
                int new_col = current->col + j;

                // 맵의 경계를 벗어난 경우
                if (new_row < 0 || new_row >= ROW || new_col < 0 || new_col >= COL) {
                    continue;
                }

                // 벽인 경우
                if (map[new_row][new_col] == 0) {
                    continue;
                }

                // 이미 방문한 노드인 경우
                if (visited[new_row][new_col]) {
                    continue;
                }

                // 새로운 노드 생성
                Node* neighbor = new Node;
                neighbor->row = new_row;
                neighbor->col = new_col;
                neighbor->parent = current;

                // 비용 계산
                int g = current->g + 1;
                int h = heuristic(new_row, new_col, end_node.row, end_node.col);
                int f = g + h;

                // 노드 정보 업데이트
                neighbor->g = g;
                neighbor->h = h;
                neighbor->f = f;

                // 인접한 노드를 큐에 추가
                pq.push(neighbor);
            }
        }
    }

    std::cout << "경로를 찾을 수 없습니다." << std::endl;
    return std::vector<Node*>();
}
*/