// create by yixian@xjkx2000

#include <ansi.h>
int main()
{
        object *ob;
        int i;
        string msg;
        
        ob=users();
        ob=filter_array(ob,(: !wizardp($1) && environment($1) && ($1->query_temp("apply/damage") > 100 || $1->query_temp("apply/armor") > 100 || $1->query_temp("apply/attack") > 100):));
        
        msg=HIC"��ҹ������б�"NOR"\n";
        i = sizeof(ob);
        
        while (i--) {
                 msg+=sprintf(NOR"%-20s "HIY"���������˺�����"HIW" %-8d "HIY" ������������"HIW" %-8d "HIY" attack��������"HIW" %-8d "NOR"\n",
                        ob[i]->query("name")+"("+ob[i]->query("id")+")",
                        ob[i]->query_temp("apply/damage"),
                        ob[i]->query_temp("apply/armor"),
						ob[i]->query_temp("apply/attack"),
                        );
                        }
                        
        msg+="\n\n";
        this_player()->start_more(msg);
        return 1;
}

