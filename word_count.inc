<?php

# counts the number of words inside an xml document
# Not perfect. Eg <a>one two<b>three four</b>five</a>
# will be stripped of xml into "one twothree fourfive"
# and will this count as three words instead of five.
# But it's good enough - whitespace is retained.

function wordCount($xml)
{
$xsl = <<< XSL
<?xml version="1.0"?>
<xsl:stylesheet
  version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
 <xsl:output method="xml" 
             encoding="utf-8" 
             omit-xml-declaration="yes" 
             cdata-section-elements="code"
             indent="no"/>
</xsl:stylesheet>
XSL;

$xsltproc = new XsltProcessor();
$xslDom = DomDocument::loadXML($xsl);
$xsltproc->importStyleSheet($xslDom);
error_reporting(0); #Hack-City
$xmlDom = DomDocument::loadXML($xml);
error_reporting(1);
$words = $xsltproc->transformToXML($xmlDom);
unset($xsltproc);

return str_word_count($words);

}

?>
