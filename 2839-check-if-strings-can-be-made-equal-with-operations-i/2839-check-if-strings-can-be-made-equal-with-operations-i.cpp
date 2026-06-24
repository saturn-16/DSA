class Solution {
public:
    bool canBeEqual(string s1, string s2) {

        string even1 = "";
        even1 += s1[0];
        even1 += s1[2];

        string odd1 = "";
        odd1 += s1[1];
        odd1 += s1[3];

        string even2 = "";
        even2 += s2[0];
        even2 += s2[2];

        string odd2 = "";
        odd2 += s2[1];
        odd2 += s2[3];

        sort(even1.begin(), even1.end());
        sort(odd1.begin(), odd1.end());
        sort(even2.begin(), even2.end());
        sort(odd2.begin(), odd2.end());

        return even1 == even2 && odd1 == odd2;
    }
};