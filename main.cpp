
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

struct Student {
    string name;
    string gender_full;
    int class_id;
    int scores[9];
    int avg_score;
    int rank;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, int> name_to_idx;
    vector<Student> all_students;
    vector<int> ranking;
    bool started = false;

    string cmd;
    while (cin >> cmd) {
        if (cmd == "ADD") {
            string name;
            char gender;
            int class_id;
            int s[9];
            cin >> name >> gender >> class_id;
            for (int i = 0; i < 9; ++i) cin >> s[i];

            if (started) {
                cout << "[Error]Cannot add student now." << "\n";
            } else if (name_to_idx.count(name)) {
                cout << "[Error]Add failed." << "\n";
            } else {
                Student st;
                st.name = name;
                st.gender_full = (gender == 'M' ? "male" : "female");
                st.class_id = class_id;
                int sum = 0;
                for (int i = 0; i < 9; ++i) {
                    st.scores[i] = s[i];
                    sum += s[i];
                }
                st.avg_score = sum / 9;
                st.rank = 0;
                name_to_idx[name] = all_students.size();
                all_students.push_back(st);
            }
        } else if (cmd == "START") {
            started = true;
            ranking.resize(all_students.size());
            for (int i = 0; i < (int)all_students.size(); ++i) {
                ranking[i] = i;
            }
            auto cmp = [&](int a, int b) {
                const Student& s1 = all_students[a];
                const Student& s2 = all_students[b];
                if (s1.avg_score != s2.avg_score) return s1.avg_score > s2.avg_score;
                for (int i = 0; i < 9; ++i) {
                    if (s1.scores[i] != s2.scores[i]) return s1.scores[i] > s2.scores[i];
                }
                return s1.name < s2.name;
            };
            sort(ranking.begin(), ranking.end(), cmp);
            for (int i = 0; i < (int)ranking.size(); ++i) {
                all_students[ranking[i]].rank = i + 1;
            }
        } else if (cmd == "UPDATE") {
            string name;
            int code, score;
            cin >> name >> code >> score;
            if (name_to_idx.count(name)) {
                int idx = name_to_idx[name];
                all_students[idx].scores[code] = score;
                int sum = 0;
                for (int i = 0; i < 9; ++i) sum += all_students[idx].scores[i];
                all_students[idx].avg_score = sum / 9;
            } else {
                cout << "[Error]Update failed." << "\n";
            }
        } else if (cmd == "FLUSH") {
            auto cmp = [&](int a, int b) {
                const Student& s1 = all_students[a];
                const Student& s2 = all_students[b];
                if (s1.avg_score != s2.avg_score) return s1.avg_score > s2.avg_score;
                for (int i = 0; i < 9; ++i) {
                    if (s1.scores[i] != s2.scores[i]) return s1.scores[i] > s2.scores[i];
                }
                return s1.name < s2.name;
            };
            sort(ranking.begin(), ranking.end(), cmp);
            for (int i = 0; i < (int)ranking.size(); ++i) {
                all_students[ranking[i]].rank = i + 1;
            }
        } else if (cmd == "PRINTLIST") {
            for (int idx : ranking) {
                const Student& st = all_students[idx];
                cout << st.rank << " " << st.name << " " << st.gender_full << " " << st.class_id << " " << st.avg_score << "\n";
            }
        } else if (cmd == "QUERY") {
            string name;
            cin >> name;
            if (name_to_idx.count(name)) {
                cout << "STUDENT " << name << " NOW AT RANKING " << all_students[name_to_idx[name]].rank << "\n";
            } else {
                cout << "[Error]Query failed." << "\n";
            }
        } else if (cmd == "END") {
            break;
        }
    }

    return 0;
}
