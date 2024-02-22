// Seive Of Erastothenes (Very optimised way of finding primes) :
int countPrimes(int n) {
    if (n <= 1) return 0;
    int count = 0;
    vector<bool> primes (n, true);
    for (int i = 2; i*i <= n; i++) {
        if (primes[i]) {
            int j = i*i;
            while (j < n) {
                primes[j] = false;
                j += i;
            }
        }
    }
    for (int i = 2; i < n; i++) {
        if (primes[i]) {
            count++;
        }
    }
    return count;
}

//Segmented Seive : 
vector<long long> findPrimes (long long n) {
    vector<long long> primes;
    vector<bool> seive(n+1, true);
    seive[0] = seive[1] = false;
    for (long long i = 2; i*i <= n; i++) {
        if (seive[i]) {
            long long j = i*i;
            while (j <= n) {
                seive[j] = false;
                j += i;
            }
        }
    }
    for (long long i = 2; i <= n; i++) {
        if (seive[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}
long long primeProduct(long long l, long long r)
{
    long long n = sqrt(r);
    vector<long long> primes = findPrimes(n);
    vector<bool> segSeive(r-l+1, true);
    for (auto pr: primes) {
        long long fm = (l/pr)*pr;
        if (fm < l) fm += pr;
        for (long long i = max(fm, pr*pr); i <= r; i += pr) {
            segSeive[i-l] = false;
        }
    }
    long long prod = 1;
    long long mod = 1e9+7;
    for (long long i = l; i <= r; i++) {
        if (segSeive[i-l]) {
            prod = (prod*(i))%mod;
        }
    }
    return prod;
}

//Find GCD : 
int gcd(int A, int B) 
{ 
    while (A > 0 && B > 0) {
        if (A > B) {
            A = A-B;
        } else {
            B = B-A;
        }
    }
    return (A == 0) ? B : A;
} 

//Fast Exponentiation :
long long int PowMod(long long int x,long long int n,long long int M)
{
    // Code here
    long long int sum = 1;
    while (n > 0) {
        if (n & 1) {
            sum = (sum*x)%M;
        }
        x = (x*x)%M;
        n >>= 1;
    }
    return (sum%M);
}