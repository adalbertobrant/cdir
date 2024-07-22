#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <utility>

using namespace std;

// Helper function to split a string
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Convert an IPv4 dotted-quad string to an integer
unsigned int ip_to_int(const string& ipaddr) {
    vector<string> octets = split(ipaddr, '.');
    if (octets.size() != 4) throw invalid_argument("Invalid IP address format");
    return (stoi(octets[0]) << 24) + (stoi(octets[1]) << 16) + (stoi(octets[2]) << 8) + stoi(octets[3]);
}

// Convert an integer to an IPv4 dotted-quad string
string int_to_ip(unsigned int ip) {
    return to_string((ip >> 24) & 0xFF) + '.' + to_string((ip >> 16) & 0xFF) + '.' + to_string((ip >> 8) & 0xFF) + '.' + to_string(ip & 0xFF);
}

// Find the starting and ending IPs of the provided CIDR
pair<unsigned int, unsigned int> cidr_to_range(const string& cidr) {
    size_t slash = cidr.find('/');
    if (slash == string::npos) {
        unsigned int start = ip_to_int(cidr);
        return {start, start};
    } else {
        string ip = cidr.substr(0, slash);
        int mbits = stoi(cidr.substr(slash + 1));
        if (mbits < 1 || mbits > 32) throw invalid_argument("Invalid network mask size");
        unsigned int start = ip_to_int(ip);
        unsigned int end = start + (1 << (32 - mbits)) - 1;
        return {start, end};
    }
}

// From a list of IP ranges, produce a list of CIDR strings that together cover all ranges
vector<string> range_to_cidrs(pair<unsigned int, unsigned int> range) {
    vector<string> outlist;
    unsigned int a = range.first;
    unsigned int b = range.second;
    unsigned int span = b - a + 1;

    if (span == 1) {
        outlist.push_back(int_to_ip(a) + "/32");
        return outlist;
    }

    int i = 0;
    while (i < 33) {
        if ((span >> i) == 1) {
            while (true) {
                if (a % (1 << i) == 0) break;
                if (i == -1) throw invalid_argument("Failed to construct a valid CIDR");
                i--;
            }
            int mbits = 32 - i;
            outlist.push_back(int_to_ip(a) + "/" + to_string(mbits));
            unsigned int consumed = (1 << i);
            unsigned int remainder = span - consumed;
            if (remainder > 0) {
                a += consumed;
                span = remainder;
                i = 0;
            } else {
                break;
            }
        } else if ((span >> i) == 0) {
            throw invalid_argument("Failed to identify suitable mask size");
        } else {
            i++;
        }
    }
    return outlist;
}

// Compare two ranges. If the two can be replaced with one, return that one range, otherwise return nullopt
optional<pair<unsigned int, unsigned int>> compare_ranges(pair<unsigned int, unsigned int> a, pair<unsigned int, unsigned int> b) {
    if (a == b) return nullopt;
    if (a.first >= b.first && a.second <= b.second) return b;
    if (b.first >= a.first && b.second <= a.second) return a;
    if (a.second + 1 == b.first) return make_optional(pair<unsigned int, unsigned int>{a.first, b.second});
    if (b.second + 1 == a.first) return make_optional(pair<unsigned int, unsigned int>{b.first, a.second});
    return nullopt;
}

