int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort (tasks.begin(), tasks.end());
        sort (workers.begin(), workers.end());
        int ans;
        int lo = 0, hi = min(tasks.size(), workers.size());
        while (lo <= hi) {
            int mid = lo + (hi-lo)/2;
            int count = 0;
            bool flag = true;
            multiset<int> ms (workers.begin(), workers.end());
            for (int i = mid-1; i >= 0; i--) {
                auto strongestWorker = prev (ms.end());
                if (tasks[i] <= *strongestWorker) {
                    ms.erase(strongestWorker);
                } else {
                    auto replacement = ms.lower_bound(tasks[i]-strength);
                    if (replacement != ms.end()) {
                        count++;
                        ms.erase(replacement);
                    } else {
                        flag = false; break;
                    }
                }
                if (count > pills) {
                    flag = false; break;
                }
            }
            if (flag) {
                ans = mid;
                lo = mid+1;
            } else {
                hi = mid-1;
            }
        }
        return ans;
    }