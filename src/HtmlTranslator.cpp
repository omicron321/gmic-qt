/** -*- mode: c++ ; c-basic-offset: 2 -*-
 *
 *  @file HtmlTranslator.cpp
 *
 *  Copyright 2017 Sebastien Fourey
 *
 *  This file is part of G'MIC-Qt, a generic plug-in for raster graphics
 *  editors, offering hundreds of filters thanks to the underlying G'MIC
 *  image processing framework.
 *
 *  gmic_qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gmic_qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gmic_qt.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "HtmlTranslator.h"
#include <QDebug>
#include <QRegularExpression>
#include "Common.h"
#include "gmic.h"

namespace GmicQt
{

QTextDocument HtmlTranslator::_document;

QString HtmlTranslator::removeTags(QString str)
{
  return str.remove(QRegularExpression("<[^>]*>"));
}

// TODO : enum param force + enum param translate
QString HtmlTranslator::html2txt(const QString & str, bool force)
{
  if (force || hasHtmlEntities(str)) {
    _document.setHtml(str);
    return fromUtf8Escapes(_document.toPlainText());
  }
  return fromUtf8Escapes(str);
}

bool HtmlTranslator::hasHtmlEntities(const QString & str)
{
  return str.contains(QRegularExpression("&[a-zA-Z]+;")) || str.contains(QRegularExpression("&#x?[0-9A-Fa-f]+;")) || str.contains(QRegularExpression("</?[a-zA-Z]*>|<[a-zA-Z]*/>"));
}

QString HtmlTranslator::fromUtf8Escapes(const QString & str)
{
  if (str.isEmpty()) {
    return str;
  }
  QByteArray ba = str.toUtf8();
  gmic_library::cimg::strunescape(ba.data());
  return QString::fromUtf8(ba);
}

} // namespace GmicQt
