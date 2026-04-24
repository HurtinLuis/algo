int minRotation(string &s) {
    int n = s.size();
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int a = s[(i + k) % n];
        int b = s[(j + k) % n];
        if (a == b) {
            k++;
        } else if (a > b) {
            i = std::max(i + k + 1, j + 1);
            k = 0;
        } else {
            j = std::max(j + k + 1, i + 1);
            k = 0;
        }
    }
    return std::min(i, j);
}