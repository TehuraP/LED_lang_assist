/*
*/

#include <crow.h>
#include "sqlite3/sqlite3.h"

struct Data{
    std::string english;
    std::string deutsch; 
};

// Callback function for SQLite
int callback(void *p, int size, char **column_text, char **column_name) {
    Data word ;
    if (size == 0) {
        return -1;
    }
    auto &vocab = *static_cast<std::string*>(p);
    word.english = column_text[1];
    word.deutsch = column_text[2];
    vocab = "\{\"English\":\"" + word.english + "\"," + "\"Deutsch\":\"" + word.deutsch + "\"\}";

    return 0;
}

int main() {
    crow::SimpleApp app;

    // Route to fetch data from the SQLite database
    CROW_ROUTE(app, "/get_data")([]() {
        sqlite3* db;
        char* zErrMsg = 0;
        int rc;
        std::string vocab;

        // Open the SQLite database
        rc = sqlite3_open("eng_deu_vocab.sqlite", &db);
        if (rc) {
            return crow::response(500, "Can't open database: " + std::string(sqlite3_errmsg(db)));
        }

        // SQL query to fetch data from the "vocabulary" table
        const char* sql = "SELECT * FROM vocabulary ORDER BY RANDOM() LIMIT 1;";

        // Execute the SQL query and use a callback function to store the results in JSON
        rc = sqlite3_exec(db, sql, callback, &vocab, &zErrMsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(zErrMsg);
            sqlite3_close(db);
            return crow::response(500, "SQL error: " + std::string(zErrMsg));
        }

        // Close the database connection
        sqlite3_close(db);

        std::string output = vocab;

        return crow::response{output}; 
    });

    // Run the Crow server on port 18080
    app.port(18080).multithreaded().run();
}
