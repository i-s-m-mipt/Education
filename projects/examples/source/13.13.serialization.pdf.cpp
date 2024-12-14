#include <filesystem>
#include <iostream>
#include <memory>

#include <PDFWriter/PageContentContext.h>
#include <PDFWriter/PDFPage.h>
#include <PDFWriter/PDFRectangle.h>
#include <PDFWriter/PDFWriter.h>

int main()
{
    auto path = "13.13.serialization.pdf.example.pdf";

//  ================================================================================================

    PDFWriter writer;
    
    std::ignore = writer.StartPDF(path, ePDFVersion17);

    auto page = std::make_unique < PDFPage > ();

    auto width = 595, height = 842;

    page->SetMediaBox(PDFRectangle(0, 0, width, height)); 

//  ================================================================================================

    auto context = writer.StartPageContentContext(page.get());

    auto line = height;

    using   Image_Options = AbstractContentContext::  ImageOptions;
    using    Text_Options = AbstractContentContext::   TextOptions;
    using Graphic_Options = AbstractContentContext::GraphicOptions;

//  ================================================================================================

    auto delta = 10, image_height = 380, ppi = 72, image_ppi = 96;

    Image_Options image_options;

    image_options.transformationMethod = AbstractContentContext::eMatrix;

    auto zoom = 1.0;

    image_options.matrix[0] = image_options.matrix[3] = zoom;

    line -= (delta + zoom * image_height * ppi / image_ppi);
    
    context->DrawImage(delta, line, "matthias.jpg", image_options);

//  ================================================================================================

    auto font = writer.GetFontForFile("consolas.ttf");

    auto font_size = 14;

    line -= (delta + font_size);

    Text_Options text_options(font, font_size, AbstractContentContext::eGray, 0);

    context->WriteText(delta, line, "Hello, World!", text_options);

//  ================================================================================================

    auto rectangle_height = font_size + 4, rectangle_width = 100;

    line -= (delta + rectangle_height);

    Graphic_Options graphic_options
    (
        AbstractContentContext::eStroke,
        AbstractContentContext::eRGB,
        AbstractContentContext::ColorValueForName("Red"), 2.0
    );

    context->DrawRectangle(delta, line, rectangle_width, rectangle_height, graphic_options);

//  ================================================================================================
    
    std::ignore = writer.EndPageContentContext(context);

    std::ignore = writer.WritePage(page.get());

    std::ignore = writer.EndPDF();

//  ================================================================================================

    std::cout << "Enter any character to continue : "; char c; std::cin >> c;

    std::filesystem::remove(path);
}
