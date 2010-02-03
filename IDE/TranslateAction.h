#ifndef TRANSLATEACTION_H
#define TRANSLATEACTION_H

#include <string>
#include <vector>
#include <map>
#include <wx/bitmap.h>
#include "GDL/Instruction.h"
class InstructionInfos;

using namespace std;

class TranslateAction
{
    public:
        //Traduire une action
        static string Translate(const Instruction & action, const InstructionInfos & infos, bool afficherPlus, bool useHTML = false);
        static string AddHTMLToParameter(string & parameter, string type);
        static void RemoveHTMLTags(string & str);

        //Boutons
        static string LabelFromType(string type);
        static wxBitmap BitmapFromType(string type);

    protected:
    private:
        TranslateAction() {};
        virtual ~TranslateAction() {};
};

#endif // TRANSLATEACTION_H