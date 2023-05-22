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

// �� �Լ�
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

// ���� �Ÿ�
int heuristic(int row, int col, int end_row, int end_col) {
    return abs(end_row - row) + abs(end_col - col);
}

// ��� ���
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
    // �켱���� ť ����
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    // ���� ��带 ť�� ����
    pq.push(&start_node);

    while (!pq.empty()) {
        // ���� ��� ����
        Node* current = pq.top();
        pq.pop();

        // �������� ������ ���
        if (current->row == end_node.row && current->col == end_node.col) {
            print_path(current);
            std::vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            return path;
        }

        // ���� ��带 �湮�� ���� �ִ� ���
        if (visited[current->row][current->col]) {
            continue;
        }
        visited[current->row][current->col] = true;

        // ������ ��� Ž��
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                // �밢�� ������ �̵��� �� ����
                if (i == 0 && j == 0 || std::abs(i) + std::abs(j) == 2) {
                    continue;
                }
                int new_row = current->row + i;
                int new_col = current->col + j;

                // ���� ��踦 ��� ���
                if (new_row < 0 || new_row >= ROW || new_col < 0 || new_col >= COL) {
                    continue;
                }

                // ���� ���
                if (map[new_row][new_col] == 0) {
                    continue;
                }

                // �̹� �湮�� ����� ���
                if (visited[new_row][new_col]) {
                    continue;
                }

                // ���ο� ��� ����
                Node* neighbor = new Node;
                neighbor->row = new_row;
                neighbor->col = new_col;
                neighbor->parent = current;

                // ��� ���
                int g = current->g + 1;
                int h = heuristic(new_row, new_col, end_node.row, end_node.col);
                int f = g + h;

                // ��� ���� ������Ʈ
                neighbor->g = g;
                neighbor->h = h;
                neighbor->f = f;

                // ������ ��带 ť�� �߰�
                pq.push(neighbor);
            }
        }
    }

    std::cout << "��θ� ã�� �� �����ϴ�." << std::endl;
    return std::vector<Node*>();
}
*/