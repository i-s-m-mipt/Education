#include <filesystem>
#include <iostream>
#include <memory>

#include <PDFWriter/PageContentContext.h>
#include <PDFWriter/PDFPage.h>
#include <PDFWriter/PDFRectangle.h>
#include <PDFWriter/PDFWriter.h>

int main()
{
    constexpr auto file = "example.pdf";

    [[maybe_unused]] PDFHummus::EStatusCode status; // note: errors handling

    PDFWriter writer;
    
    status = writer.StartPDF(file, ePDFVersion13);

    const auto page = std::make_unique < PDFPage > ();

    page->SetMediaBox(PDFRectangle(0, 0, 210, 297)); // note: A4 page

    auto context = writer.StartPageContentContext(page.get());
    
    context->DrawImage(10, 10, "matthias.jpg");
    
    status = writer.EndPageContentContext(context);

    status = writer.WritePage(page.get());

    status = writer.EndPDF();

    std::cout << "Enter any character to continue: "; char c{}; std::cin >> c;

    std::remove(file);

    return 0;
}