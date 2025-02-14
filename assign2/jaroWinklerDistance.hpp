double jaroWinklerDistance(const std::string& str1, const std::string& str2) {
    const size_t len1 = str1.length();
    const size_t len2 = str2.length();
    if (len1 == 0 || len2 == 0) {
        return 0.0;
    }

    const size_t matchDistance = std::max(len1, len2) / 2 - 1;
    std::vector<bool> str1Matches(len1, false);
    std::vector<bool> str2Matches(len2, false);

    size_t matches = 0;
    for (size_t i = 0; i < len1; ++i) {
        const size_t start = std::max(i > matchDistance ? i - matchDistance : 0, size_t(0));
        const size_t end = std::min(i + matchDistance + 1, len2);
        for (size_t j = start; j < end; ++j) {
            if (!str2Matches[j] && str1[i] == str2[j]) {
                str1Matches[i] = true;
                str2Matches[j] = true;
                ++matches;
                break;
            }
        }
    }

    if (matches == 0) {
        return 0.0;
    }

    size_t transpositions = 0;
    size_t k = 0;
    for (size_t i = 0; i < len1; ++i) {
        if (str1Matches[i]) {
            while (!str2Matches[k]) {
                ++k;
            }
            if (str1[i] != str2[k]) {
                ++transpositions;
            }
            ++k;
        }
    }

    double jaro = (static_cast<double>(matches) / len1 +
                   static_cast<double>(matches) / len2 +
                   (matches - transpositions / 2.0) / matches) / 3.0;

    // Jaro-Winkler 调整
    const double winklerWeight = 0.1;
    size_t prefix = 0;
    for (size_t i = 0; i < std::min(len1, len2); ++i) {
        if (str1[i] == str2[i]) {
            ++prefix;
        } else {
            break;
        }
    }

    return jaro + prefix * winklerWeight * (1.0 - jaro);
}
/*


int main() {
    // std::string str1 = "MARTHA";
    // std::string str2 = "MARHTA";
    std::string myName = "Benkang Peng";
    std::vector<std::string> matches{"Bentlee Peck", "Brodie Parks", 
                                     "Brielle Poole", "Beckett Pineda"};

    for(auto& name : matches){
        std::cout << jaroWinklerDistance(myName , name) << std::endl;
    }
    // double distance = jaroWinklerDistance(str1, str2);
    // std::cout << "Jaro-Winkler Distance: " << distance << std::endl;

    return 0;
}
*/