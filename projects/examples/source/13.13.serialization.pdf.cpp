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

    [[maybe_unused]] constexpr auto width = 595, height = 842, dpi = 72; // note: A4 page in 72 DPI

    page->SetMediaBox(PDFRectangle(0, 0, width, height)); 

    auto context = writer.StartPageContentContext(page.get());

    auto line = height; // note: current output line from top of page

    constexpr auto image_height = 380, image_dpi = 96, delta = 10;

    AbstractContentContext::ImageOptions image_options;

    image_options.transformationMethod = AbstractContentContext::eMatrix;

    constexpr auto zoom = 1.0;

    image_options.matrix[0] = image_options.matrix[3] = zoom;

    line -= (delta + zoom * image_height * dpi / image_dpi);
    
    context->DrawImage(delta, line, "matthias.jpg", image_options);

    auto font = writer.GetFontForFile("consolas.ttf");

    constexpr auto font_size = 14;

    AbstractContentContext::TextOptions text_options(font, font_size, AbstractContentContext::eGray, 0);

    line -= (delta + font_size);
    
    context->WriteText(delta, line, "Hello, World!", text_options);

    AbstractContentContext::GraphicOptions graphic_options(AbstractContentContext::eStroke,
                                                           AbstractContentContext::eRGB,
                                                           AbstractContentContext::ColorValueForName("Red"),
                                                           2.0);

    constexpr auto rectangle_height = font_size + 4, rectangle_width = 100;
    
    line -= (delta + rectangle_height);

    context->DrawRectangle(delta, line, rectangle_width, rectangle_height, graphic_options);
    
    status = writer.EndPageContentContext(context);

    status = writer.WritePage(page.get());

    status = writer.EndPDF();

    std::cout << "Enter any character to continue: "; char c{}; std::cin >> c;

    std::remove(file);

    return 0;
}