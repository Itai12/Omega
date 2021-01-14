#include "list_book_controller.h"

namespace reader
{

View* ListBookController::view()
{
    return &m_tableView;
}

ListBookController::ListBookController(Responder * parentResponder):
    ViewController(parentResponder),
    m_tableView(this, this)
{
    m_files[0].name= "Harry Potter 1.txt";
    m_files[1].name= "hey.txt";
    m_nbFiles = 2;
}

int ListBookController::numberOfRows() const
{
    return m_nbFiles;
}

KDCoordinate ListBookController::cellHeight()
{
    return 50;
}

HighlightCell * ListBookController::reusableCell(int index)
{
    return &m_cells[index];
}
    
int ListBookController::reusableCellCount() const
{
    return NB_CELLS;
}

void ListBookController::willDisplayCellForIndex(HighlightCell * cell, int index)
{
    MessageTableCell* myTextCell = static_cast<MessageTableCell*>(cell);    
    MessageTextView* textView = static_cast<MessageTextView*>(myTextCell->labelView());
    textView->setText(m_files[index].name);
    myTextCell->setMessageFont(KDFont::LargeFont);
}

}

