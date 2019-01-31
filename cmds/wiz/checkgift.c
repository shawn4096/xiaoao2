// create by renlai@xa

#include <ansi.h>
int main()
{
        object *ob;
        int i;
        string msg;
        
        ob=users();
        ob=filter_array(ob,(: !wizardp($1) && environment($1) && ($1->query_temp("apply/strength") > 50 || $1->query_temp("apply/strength") <0 || $1->query_temp("apply/dexerity") <0 || $1->query_temp("apply/dexerity") > 100 || $1->query_temp("apply/parry") > 100):));
        
        msg=HIC"玩家属性异常列表："NOR"\n";
        i = sizeof(ob);
        
        while (i--) {
                 msg+=sprintf(NOR"%-20s "HIY"附加臂力："HIW" %-8d "HIY" 附加身法："HIW" %-8d "HIY" 附加招架："HIW" %-8d "NOR"\n",
                        ob[i]->query("name")+"("+ob[i]->query("id")+")",
                        ob[i]->query_temp("apply/strength"),
                        ob[i]->query_temp("apply/dexerity"),
						ob[i]->query_temp("apply/parry"),
                        );
                        }
                        
        msg+="\n\n";
        this_player()->start_more(msg);
        return 1;
}

