// create by renlai@xa

#include <ansi.h>
int main()
{
        object *ob;
        int i;
        string msg;
        
        ob=users();
        ob=filter_array(ob,(: !wizardp($1) && environment($1) && ($1->query_temp("apply/intelligence") > 50 || $1->query_temp("apply/intelligence") <0 || $1->query_temp("apply/constitution") <0 || $1->query_temp("apply/constitution") > 100 || $1->query_temp("apply/attack") > 100):));
        
        msg=HIC"��������쳣�б�"NOR"\n";
        i = sizeof(ob);
        
        while (i--) {
                 msg+=sprintf(NOR"%-20s "HIY"����������"HIW" %-8d "HIY" ���Ӹ��ǣ�"HIW" %-8d "HIY" �������У�"HIW" %-8d "NOR"\n",
                        ob[i]->query("name")+"("+ob[i]->query("id")+")",
                        ob[i]->query_temp("apply/intelligence"),
                        ob[i]->query_temp("apply/constitution"),
						ob[i]->query_temp("apply/attack"),
                        );
                        }
                        
        msg+="\n\n";
        this_player()->start_more(msg);
        return 1;
}
