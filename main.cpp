#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <optional>
#include <algorithm>
#include <thread>

class Document
{
public:
    std::string name;
    std::string content;
};
void print(const Document &document)
{
    std::cout << "Document Name: \n"
              << document.name << '\n';
    std::cout << "Content:\n"
              << document.content;
}
class Catalog
{
public:
    void add(Document document)
    {
        documents.push_back(std::move(document));
    }

    void print_all() const
    {
        for (const Document &document : documents)
        {
            print(document);
        }
    }
    int size() const
    {
        return documents.size();
    }
    const Document *find_by_name(const std::string &filename) const
    {
        auto it = std::find_if(documents.begin(), documents.end(), [&filename](const Document &doc)
                               { return doc.name == filename; });
        return it != documents.end() ? &(*it) : nullptr;
    }

private:
    std::vector<Document> documents;
};
Document create_document(const std::string &name, const std::string &content)
{
    Document doc;
    doc.name = name;
    doc.content = content;
    return doc;
}
std::optional<Document> read_document(const std::string &filename)
{

    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Could not open " << filename << '\n'; 
        return std::nullopt;
    }
    std::string line;
    std::string content;
    while (std::getline(file, line))
    {
        content += line + '\n';
    }
    return create_document(filename, content);
}
std::vector<Document> load_documents_parallel(const std::vector<std::string> &filenames)
{
    // One result slot per filename. Empty means that file didn't load.
    std::vector<std::optional<Document>> results(filenames.size());
    std::vector<std::thread> workers;

    for (std::size_t i = 0; i < filenames.size(); ++i)
    {
        workers.emplace_back([&, i]
                             { results[i] = read_document(filenames[i]); });
    }

    // Wait for all file-reading work to finish.
    for (std::thread &worker : workers)
    {
        worker.join();
    }

    // Gather only successful results, in the original filename order.
    std::vector<Document> documents;
    for (auto &result : results)
    {
        if (result)
        {
            documents.push_back(std::move(*result));
        }
    }

    return documents;
}
int main()
{
std::vector<std::string> filenames{
    "sample.txt",
    "sample2.txt",
    "missing.txt"
};

auto documents = load_documents_parallel(filenames);

Catalog catalog;
for (Document& document : documents) {
    catalog.add(std::move(document));
}

catalog.print_all();
}