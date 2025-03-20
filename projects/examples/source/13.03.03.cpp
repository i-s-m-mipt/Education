#include <filesystem>
#include <iostream>
#include <memory>
#include <utility>

#include <PDFWriter/PageContentContext.h>
#include <PDFWriter/PDFPage.h>
#include <PDFWriter/PDFRectangle.h>
#include <PDFWriter/PDFWriter.h>

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    PDFWriter writer;

//  ----------------------------------------------------------------------------------------
    
    writer.StartPDF("13.03.03.pdf", ePDFVersion17);

//  ----------------------------------------------------------------------------------------

    auto page = std::make_unique < PDFPage > ();

//  ----------------------------------------------------------------------------------------

    page->SetMediaBox(PDFRectangle(0, 0, 595, 842));

//  ----------------------------------------------------------------------------------------

    using   Image_Options = AbstractContentContext::  ImageOptions;

    using    Text_Options = AbstractContentContext::   TextOptions;

    using Graphic_Options = AbstractContentContext::GraphicOptions;

//  ----------------------------------------------------------------------------------------

    auto delta = 10, line = static_cast < int > (page->GetMediaBox().UpperRightY);

//  ----------------------------------------------------------------------------------------

    auto context = writer.StartPageContentContext(page.get());

//  ----------------------------------------------------------------------------------------

    auto font = writer.GetFontForFile("13.03.04.ttf");

    auto font_size = 16;

//  ----------------------------------------------------------------------------------------

    line -= delta + font_size;

//  ----------------------------------------------------------------------------------------

    Text_Options text_options(font, font_size, AbstractContentContext::eGray, 0);

//  ----------------------------------------------------------------------------------------

    context->WriteText(delta, line, "Hello, World!", text_options);

//  ----------------------------------------------------------------------------------------

    auto image_height = 380, ppi = 72, image_ppi = 96;

    auto zoom = 1.0;

//  ----------------------------------------------------------------------------------------

    line -= delta + zoom * image_height * ppi / image_ppi;

//  ----------------------------------------------------------------------------------------

    Image_Options image_options;

    image_options.transformationMethod = AbstractContentContext::eMatrix;

    image_options.matrix[0] = image_options.matrix[3] = zoom;

//  ----------------------------------------------------------------------------------------
    
    context->DrawImage(delta, line, "13.03.05.jpg", image_options);

//  ----------------------------------------------------------------------------------------

    auto rectangle_width = 100, rectangle_height = font_size + 4;

//  ----------------------------------------------------------------------------------------

    line -= delta + rectangle_height;

//  ----------------------------------------------------------------------------------------

    Graphic_Options graphic_options
    (
        AbstractContentContext::eStroke,
        
        AbstractContentContext::eRGB,

        AbstractContentContext::ColorValueForName("Red"), 2
    );

//  ----------------------------------------------------------------------------------------

    context->DrawRectangle(delta, line, rectangle_width, rectangle_height, graphic_options);

//  ----------------------------------------------------------------------------------------
    
    writer.EndPageContentContext(context);

    writer.WritePage(page.get());

    writer.EndPDF();

//  ----------------------------------------------------------------------------------------

    std::cout << "main : enter char : "; std::cin.get();

//  ----------------------------------------------------------------------------------------

    std::filesystem::remove(writer.GetOutputFile().GetFilePath());
}
