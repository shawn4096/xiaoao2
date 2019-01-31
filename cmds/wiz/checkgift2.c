// create by renlai@xa

#include <ansi.h>
int main()
{
        object *ob;
        int i;
        string msg;
        
        ob=users();
        ob=filter_array(ob,(: !wizardp($1) && environment($1) && ($1->query_temp("apply/intelligence") > 50 || $1->query_temp("apply/intelligence") <0 || $1->query_temp("apply/constitution") <0 || $1->query_temp("apply/constitution") > 100 || $1->query_temp("apply/attack") > 100):));
        
        msg=HIC"玩家属性异常列表："NOR"\n";
        i = sizeof(ob);
        
        while (i--) {
                 msg+=sprintf(NOR"%-20s "HIY"附加智力："HIW" %-8d "HIY" 附加根骨："HIW" %-8d "HIY" 附加命中："HIW" %-8d "NOR"\n",
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
