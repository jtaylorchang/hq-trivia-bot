#include "tests.hpp"

int pass_count_ = 0;
int fail_count_ = 0;

/**
 * Run in test mode
 */
void RunTestMode() {
    PrintColorful("Running in TEST mode", MAGENTA);
    RunTests();
    PrintResults();
}

/**
 * Run all the tests
 */
void RunTests() {
    RunSectionMaps();
    RunSectionDoubles();
    RunSectionStringManipulation();
    RunSectionStringProperties();
    RunSectionNumberConversions();
    RunSectionWordComplexity();
}

/**
 * Run tests regarding maps and keys / values
 */
void RunSectionMaps() {
    PrintColorful("SECTION: MAPS", YELLOW);
    
    map<string, string> test_map;
    map<string, string> empty_map;
    SetMapValue(test_map, "test", "this is a test");
    SetMapValue(test_map, "test2", "this is another test");
    
    vector<string> expected_keys = {
        "test",
        "test2"
    };
    vector<string> expected_values = {
        "this is a test",
        "this is another test"
    };
    Assert("Getting map keys", expected_keys == GetMapKeys(test_map));
    Assert("Getting map values", expected_values == GetMapValues(test_map));
    Assert("Getting map keys empty", GetMapKeys(empty_map).empty());
    Assert("Getting map values empty", GetMapValues(empty_map).empty());
}

/**
 * Run tests regarding equality of doubles
 */
void RunSectionDoubles() {
    PrintColorful("SECTION: DOUBLE EQUALITY", YELLOW);
    
    Assert("Checking equal doubles", ApproxEquals(0.5001, 0.5001));
    Assert("Checking equal doubles beyond tolerance", !ApproxEquals(0.5, 0.52));
}

/**
 * Run tests regarding string manipulations
 */
void RunSectionStringManipulation() {
    PrintColorful("SECTION: STRING MANIPULATION", YELLOW);
    
    Assert("Replacing string", Replace("this is a test", "is a", "is not a") == "this is not a test");
    Assert("Replacing empty string", Replace("", "test", "test") == "");
    Assert("Replacing with empty string", Replace("test", "", "test") == "test");
    
    vector<string> split_by_char = {
        "this", "is", "a", "test"
    };
    Assert("Splitting string by char", Split("this is a test", ' ') == split_by_char);
    Assert("Splitting string by char DNE", Split("this is a test", 'z').size() == 1);
    
    Assert("Trimming leading spaces", Trim("   test") == "test");
    Assert("Trimming trailing spaces", Trim("test   ") == "test");
    Assert("Trimming padded spaces", Trim("  test  ") == "test");
    Assert("Trimming other trim values", Trim("\ntest") == "test");
    
    Assert("Lowercase of string", ToLowerCase("This Is A Test") == "this is a test");
    Assert("Lowercase of all caps", ToLowerCase("THIS IS A TEST") == "this is a test");
    Assert("Lowercase of meme", ToLowerCase("tHiS iS a TeSt") == "this is a test");
    Assert("Lowercase of empty string", ToLowerCase("") == "");
    
    Assert("Url encoding spaces", UrlEncode("this is a test") == "this%20is%20a%20test");
    Assert("Url encoding a percentage sign", UrlEncode("%%%") == "");
    Assert("Url encoding multiple symbols", UrlEncode("this isn't a test") == "this%20isn%27t%20a%20test");
    Assert("Url encoding an empty string", UrlEncode("") == "");
}

/**
 * Run tests regarding string properties
 */
void RunSectionStringProperties() {
    PrintColorful("SECTION: STRING PROPERTIES", YELLOW);
    
    Assert("Counting a char", Count("this is a test", 't') == 3);
    Assert("Counting a char DNE", Count("this is a test", 'z') == 0);
    Assert("Counting a string", Count("this is a test", "is") == 2);
    Assert("Counting a string DNE", Count("this is a test", "apple") == 0);
    Assert("Counting a string that is a char", Count("this is a test", "t") == 3);
    
    Assert("Contains a substring", Contains("this is a test", "test"));
    Assert("Contains a substring DNE", !Contains("this is a test", "apple"));
    Assert("Contains one of a vector", ContainsOneOf("this is a test", {"apple", "is"}));
    Assert("Contains none of a vector", !ContainsOneOf("this is a test", {"apple", "pear"}));
    Assert("Contains one of an empty vector", !ContainsOneOf("this is a test", {}));
}

/**
 * Run tests regarding converting numbers to english
 */
void RunSectionNumberConversions() {
    PrintColorful("SECTION: NUMBER CONVERSION", YELLOW);
    
    Assert("Is convertable to number", IsConvertableNumber("10"));
    Assert("Is convertable to number negative", IsConvertableNumber("-10"));
    Assert("Is not convertable to number", !IsConvertableNumber("10a"));
    Assert("Is not convertable to number too long", !IsConvertableNumber("1000"));
    
    Assert("Numeral to english", NumeralToEnglish(10) == "ten");
    Assert("Numeral to english small", NumeralToEnglish(2) == "two twice");
    Assert("Numeral to english too large", NumeralToEnglish(100) == "");
}

/**
 * Run tests regarding word complexity
 */
void RunSectionWordComplexity() {
    PrintColorful("SECTION: WORD COMPLEXITY", YELLOW);
    
    Assert("Is complex word", IsComplex("computer"));
    Assert("Is complex word short", !IsComplex("the"));
    Assert("Is complex word empty", !IsComplex(""));
}

/**
 * Print the full test results after the tests are done
 */
void PrintResults() {
    cout << endl;
    PrintColorful("FINISHED " + std::to_string(pass_count_ + fail_count_) + " TESTS", MAGENTA);
    
    if (pass_count_ > 0) {
        PrintColorful("Passed: " + std::to_string(pass_count_), GREEN);
    }
    if (fail_count_ > 0) {
        PrintColorful("Failed: " + std::to_string(fail_count_), RED);
    }
}

/**
 * Checks if a boolean is true, and changes the appropriate test counts and prints
 */
void Assert(string message, bool condition) {
    cout << "Asserting: " << message << endl;
    if (condition) {
        PrintColorful("Test passed", GREEN);
        pass_count_++;
    } else {
        PrintColorful("Test failed", RED);
        fail_count_++;
    }
}
