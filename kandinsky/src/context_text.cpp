#include <kandinsky/context.h>
#include "font.h"

KDColor characterBuffer[BITMAP_FONT_CHARACTER_WIDTH*BITMAP_FONT_CHARACTER_HEIGHT];

void KDContext::drawChar(char character, KDPoint p, KDColor textColor, KDColor backgroundColor) {
  for (int j=0; j<BITMAP_FONT_CHARACTER_HEIGHT;j++) {
    for (int i=0; i<BITMAP_FONT_CHARACTER_WIDTH;i++) {
      uint8_t intensity = bitmapFont[character-BITMAP_FONT_FIRST_CHARACTER][j][i];
      KDColor color = KDColor::blend(textColor, backgroundColor, intensity);
      //characterBuffer[j*BITMAP_FONT_CHARACTER_WIDTH+i] = color;
      characterBuffer[j*BITMAP_FONT_CHARACTER_WIDTH+i] = color;
    }
  }
  fillRectWithPixels(KDRect(p, BITMAP_FONT_CHARACTER_WIDTH, BITMAP_FONT_CHARACTER_HEIGHT),
      characterBuffer,
      characterBuffer);
}
#if 0
void KDContext::drawChar(char character, KDPoint p, uint8_t inverse) {
  for (int j=0; j<BITMAP_FONT_CHARACTER_HEIGHT;j++) {
    for (int i=0; i<BITMAP_FONT_CHARACTER_WIDTH;i++) {
      uint8_t intensity = inverse ?
        bitmapFont[character-BITMAP_FONT_FIRST_CHARACTER][j][i] :
        (0xFF-bitmapFont[character-BITMAP_FONT_FIRST_CHARACTER][j][i]);
      KDColor color(intensity * 0x010101);
      characterBuffer[j*BITMAP_FONT_CHARACTER_WIDTH+i] = color;
    }
  }
  fillRectWithPixels(KDRect(p, BITMAP_FONT_CHARACTER_WIDTH, BITMAP_FONT_CHARACTER_HEIGHT),
      characterBuffer,
      characterBuffer);
}
#endif

void KDContext::drawString(const char * text, KDPoint p, KDColor textColor, KDColor backgroundColor) {
  KDPoint position = p;
  KDPoint characterSize(BITMAP_FONT_CHARACTER_WIDTH, 0);
  while(*text != 0) {
    drawChar(*text, position, textColor, backgroundColor);
    text++;
    position = position.translatedBy(characterSize);
  }
}

void KDContext::blendChar(char character, KDPoint p, KDColor textColor) {
  KDRect absoluteRect = absoluteFillRect(KDRect(p, BITMAP_FONT_CHARACTER_WIDTH, BITMAP_FONT_CHARACTER_HEIGHT));
  pullRect(absoluteRect, characterBuffer);
  KDCoordinate startingI = m_clippingRect.x() - p.translatedBy(m_origin).x();
  KDCoordinate startingJ = m_clippingRect.y() - p.translatedBy(m_origin).y();
  startingI = startingI > 0 ? startingI : 0;
  startingJ = startingJ > 0 ? startingJ : 0;
  for (KDCoordinate j=0; j<absoluteRect.height(); j++) {
    for (KDCoordinate i=0; i<absoluteRect.width(); i++) {
      KDColor * currentPixelAdress = characterBuffer + i + absoluteRect.width()*j;
      uint8_t intensity = bitmapFont[character-BITMAP_FONT_FIRST_CHARACTER][j + startingJ][i +startingI];
      *currentPixelAdress = KDColor::blend(textColor, *currentPixelAdress, intensity);
    }
  }
  pushRect(absoluteRect, characterBuffer);
}

void KDContext::blendString(const char * text, KDPoint p, KDColor textColor) {
  KDPoint position = p;
  KDPoint characterSize(BITMAP_FONT_CHARACTER_WIDTH, 0);
  while(*text != 0) {
    blendChar(*text, position, textColor);
    text++;
    position = position.translatedBy(characterSize);
  }
}
