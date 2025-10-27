//////////////////////////////////////////////////////////////////////////////////////////////

#include <filesystem>
#include <iostream>
#include <memory>
#include <print>

//////////////////////////////////////////////////////////////////////////////////////////////

#include <PDFWriter/AbstractContentContext.h>
#include <PDFWriter/PageContentContext.h>
#include <PDFWriter/PDFPage.h>
#include <PDFWriter/PDFRectangle.h>
#include <PDFWriter/PDFWriter.h>

//////////////////////////////////////////////////////////////////////////////////////////////

void add_text(int & line, int delta, PageContentContext & context, PDFWriter & writer)
{
    auto font = writer.GetFontForFile("font.ttf");

    auto size = 16;

    line -= delta + size;

    AbstractContentContext::TextOptions options(font, size, AbstractContentContext::eGray, 0);

    context.WriteText(delta, line, "Hello, World!", options);
}

//////////////////////////////////////////////////////////////////////////////////////////////

void add_image(int & line, int delta, PageContentContext & context)
{
    auto height = 380, ppi_1 = 72, ppi_2 = 96;

    auto zoom = 1.0;

    line -= delta + zoom * height * ppi_1 / ppi_2;

    AbstractContentContext::ImageOptions options;

    options.transformationMethod = AbstractContentContext::eMatrix;

    options.matrix[0] = options.matrix[3] = zoom;
    
    context.DrawImage(delta, line, "image.jpg", options);
}

//////////////////////////////////////////////////////////////////////////////////////////////

void add_graphic(int & line, int delta, PageContentContext & context)
{
    auto width = 100, height = 100;

    line -= delta + height;

    AbstractContentContext::GraphicOptions options
    (
        AbstractContentContext::eStroke,
        
        AbstractContentContext::eRGB,

        AbstractContentContext::ColorValueForName("Red"), 2
    );

    context.DrawRectangle(delta, line, width, height, options);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    PDFWriter writer;

//  --------------------------------------------------------------
    
    writer.StartPDF("output.pdf", EPDFVersion::ePDFVersionMax);

//  --------------------------------------------------------------

    auto page = std::make_unique < PDFPage > ();

//  --------------------------------------------------------------

    auto line = 842, delta = 10;

//  --------------------------------------------------------------

    page->SetMediaBox(PDFRectangle(0, 0, 595, line));

//  --------------------------------------------------------------

    auto context = writer.StartPageContentContext(page.get());

//  --------------------------------------------------------------

    add_text   (line, delta, *context, writer);

    add_image  (line, delta, *context);

    add_graphic(line, delta, *context);

//  --------------------------------------------------------------
    
    writer.EndPageContentContext(context);

    writer.WritePage(page.get());

    writer.EndPDF();

//  --------------------------------------------------------------

    std::print("main : enter char : "); std::cin.get();

//  --------------------------------------------------------------

    std::filesystem::remove(writer.GetOutputFile().GetFilePath());
}

//////////////////////////////////////////////////////////////////////////////////////////////