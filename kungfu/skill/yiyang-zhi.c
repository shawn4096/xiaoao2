//cool@SJ,19990628
// Modified by snowman@SJ 20/08/2000
// Modified by Cool@SJ 09/10/2000,change autopfm and yyz_hurt as qishang-quan.
// Update By lsxk@hsbbs 2007/6/13 add ����6��Ч��
/*
        ����-----------�м�����ɶԷ��޷�exert,�����һ��ָ����
        �ٳ�-----------�м���ʹ�Է���ʧ��һ�ι������м��ʴ�ɶԷ�����,�������æ��.
        �س�-----------�м���ʹ�õз��޷�perform,�����һ��ָ����
        �г�-----------�м����ܵ�һ���屶�˺������ƻ����߻�����
        ����-----------�м��ʽ���������
        ����-----------�м�����������˺�,������һ��ָ����
                                           By lsxk@hsbbs 2007/6/13
*/

#include <ansi.h>
#include <skill.h>

inherit SKILL;
#include "/kungfu/skill/eff_msg.h";
#include "/kungfu/skill/yiyang-zhi/liumai_skill_msg.h"

string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
"ӿȪѨ","��׶Ѩ","�縮Ѩ",
}); 

string Gmsg;

mapping *action_finger = ({
([
        "action" : "�����������죬һ����͵�������$N��ָӿ��������һ�С�����ů�ڡ�����������$n$l",
        "weapon" : "һ��ָ��",
        "force": 200,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "����ů��",
	    "lvl": 0,
        "damage_type" : "����"
]),
([
        "action" : "$N����ʳָ΢�㣬���С������������һ���ۻ��һ��ָ������$n�����ֳ��ȣ���������",
        "weapon" : "һ��ָ��",
        "force": 150,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "�������",
	"lvl": 20,
        "damage_type" : "����"
]),
([
        "action" : "$Nһָ���ճ�ϼ�⡹��������һ�����ӿ��$n���������´�ƽ�ͣ�����Ȼ����޿��뿹",
        "weapon" : "һ��ָ��",
        "force": 180,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "�ճ�ϼ��",
	    "lvl": 30,
        "damage_type" : "����"
]),
([
        "action" : "�����������죬һ����͵�������$N��ָӿ��������һ�С�����ů�ڡ�����������$n$l",
        "weapon" : "һ��ָ��",
        "force": 220,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "����ů��",
	    "lvl": 40,
        "damage_type" : "����"
]),
([
        "action" : "$N̤ǰһ������ָ�������һ�㣬$nֻ����Ϣһ�����ѱ������ս������ĸ�����������$l",
        "weapon" : "��������",
        "force": 260,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "���ս���",
	    "lvl": 50,
        "damage_type" : "����"
]),
([
        "action" : "$N������ڣ������������׻ӳ���ӿ��$n��$l���������������һ�С�������ů��",
        "skill_name" : "������ů",
        "force": 300,
        "dodge": random(20),
        "parry": random(10),
        "weapon" : "һ��ָ��",
	    "lvl": 60,
        "damage_type" : "����"
]),
([
        "action" : "$N���΢Ц�������ʳָ����������$n�ؿڣ����С�ĺ��ӳ�ա�����������ȴ��˿���ƿ�֮��",
        "weapon" : "һ��ָ��",
        "force": 330,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "ĺ��ӳ��",
	    "lvl": 70,
        "damage_type" : "����"
]),
([
        "action" : "ֻ��$Nʳָ΢����һָ������Ǭ�������������ɭ�ϣ�Ӻ�����£�������֮�в������߷�ȣ�",
        "weapon" : "��������",
        "force": 380,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "����Ǭ��",
	    "lvl": 80,
        "damage_type" : "����"
]),
([     
        "action" : "$Nͷ�������뵣����۽�Ũ����������һ�㣬ʳָ�����һʽ��������̩������$n��",
        "weapon" : "��������",
        "force": 420,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "������̩",
    	"lvl": 90,
        "damage_type" : "����"
])
});

mapping *action_sword = ({
([
        "action" : "$N�����Ц����$wƽ�أ���׼ʱ��һ���̳����������������Ѹ���ޱȵ�ֱ��$n$l",
	    "lvl":0,
        "damage_type" : "����",
]),
([ 
        "action" : "$N����������������󴫶�����һ��ָ�񹦻���$w֮�ϣ��������أ�ƽƽ�����ش���$n",
	    "lvl":20,
        "damage_type" : "����",
]),
([ 
        "action" : "ֻ��$N��Ϣ���񣬽Ų����ţ����ߵ��ƣ�һʽ����������$n$l����ʽ��������",
	     "lvl":30,
        "damage_type" : "����",
]),
([
        "action" : "$N���²���΢�䣬���潣�ߣ��������أ���Ʈ�ݵ�һ����$n�̳���������ȴҲ��ʧ��������",
		"lvl":100,
        "damage_type" : "����",
]),
([
        "action" : "$Nƽ��һ�������е�$w���ƽ������أ�ʹ��ʱ�Ա���ǰ��ɬ����ʵ�Ǿ������أ�����֮��",
	    "lvl":180,
        "damage_type" : "����",
]),
});

int valid_enable(string usage) 
{  
       //����ָ����ȡ������sword by sohu
	   return usage=="finger" || usage=="parry" ; 
}

int valid_learn(object me)
{     
       if ((string)me->query("gender") != "����") 
                return notify_fail("һ��ָ���Ǵ�������������ο�����ϰ��\n");
       if (!me->query("quest/tls/yyz/pass")) 
                return notify_fail("һ��ָ������Ͼ������㲻�ö����洫��ο�����ϰ��\n");

	   if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��һ��ָ������֡�\n");
       if ((int)me->query("max_neili") < 1000)
                return notify_fail("�������̫�����޷���һ��ָ��\n");
       return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action_finger)-1; i >= 0; i--)
                return action_finger[i]["skill_name"];
}
void skill_improved(object me)
{
	int i = (int)me->query_skill("yiyang-zhi", 1);   

	if (i == 100)
	{
		 tell_object(me,HIY"�㾭���������������ڽ�һ��ָ��������Ʒ���硣\n");
	     me->set("yyz/degree",9);
	 }
	if (i == 200)
	{
		tell_object(me,HIY"�㾭���������������ڽ�һ��ָ��������Ʒ���硣��\n");
        me->set("yyz/degree",8);
	 }
	if (i == 300) 
	{
		tell_object(me,HIY"�㾭���������������ڽ�һ��ָ��������Ʒ���硣��\n");
        me->set("yyz/degree",7);
	 }
	if (i == 350)
	  {
		tell_object(me,HIY"�㾭���������������ڽ�һ��ָ��������Ʒ���硣��\n");
        me->set("yyz/degree",6);
	 }
	if (i == 400)
     {
		tell_object(me,HIY"�㾭���������������ڽ�һ��ָ��������Ʒ���硣��\n");
        me->set("yyz/degree",5);
	 }
	if (i == 450)
    {
		tell_object(me,HIY"�㾭���������������ڽ�һ��ָ��������Ʒ���硣��\n");
        me->set("yyz/degree",4);
	 }
	if (i == 500)
	{
		tell_object(me,HIY"�㾭���������������ڽ�һ��ָ��������Ʒ���硣��\n");
        me->set("yyz/degree",3);
	 }
	if (i == 550)
	{
		tell_object(me,HIY"�㾭���������������ڽ�һ��ָ��������Ʒ���硣��\n");
        me->set("yyz/degree",2);
	 }
	if (i == 600)
	 {
		tell_object(me,HIY"�㾭���������������ڽ�һ��ָ������һƷ���硣һ��ָ���ڴ�ɡ�\n");
        me->set("yyz/degree",1);
	 }

}
mapping query_action(object me, object weapon)
{
        int i, level, n,j;
        mapping skill_name;
        string msg,msglm, *lmsj_msg;

        level = me->query_skill("yiyang-zhi",1);
        me->delete_temp("hit_ob_hit");
        //һ��ָ����������Ч
		if( objectp(weapon) ){
           for(i = sizeof(action_sword); i > 0; i--) { 
			if(level >= action_sword[i-1]["lvl"]) {
				j = NewRandom(i, 20, level/5);
				return ([
					"action": action_sword[j]["action"],
					"lvl": action_sword[j]["lvl"],
					"damage_type": action_sword[j]["damage_type"],
					"force": 150 + random(300),
					"dodge": random(30),
					"parry": random(30),
					"damage": 100+ random(100),
				]);
			}
		   }
		}        
          //yz3m,����һָ����
         if( intp(n = me->query_temp("yyz/yz3m")) && n > 0 ){
                switch(n){
                   case 4: msg = "$N����Ծ�����Ƹ��أ�����ʳָ�������ʽδ�ϣ��������أ��������磬����ָ֮�������޷ֺ�ƫ�������\n"+
                               "$n��ǿ�䡢�Ի����縮����׵���յ����������������̨�����ȶ�����ʮ��Ѩ"; break;
				   case 3: msg = "$N����ʳָ΢����ͻȻ�����ʹ�ľ�Ȼ���ǣ�һ��ָ��������$Nʳָ�϶��������仺��$n�ϰ��������Ѩ\n"+
                                "ȴ��ȫ��$Nһָ����֮�£�����֪Ҫ�������һ��Ѩ�����Ŵ���Ѩ�Դ�ָ֮��";break;
                   case 2: msg = "$N����δ�꣬��������������һָ��������ȴ��ָ��$nС������һָ�����ֵ�ҪѨ���㣬�Ǹ������ʮ����Ѩ�������š�\n"+
                                "ͨ�ȣ�������ע��������ֱ�ֺ�ǡ���������������һָ����֮��"; break;
                   case 1: msg = "���ŵ���ָ�ֳ�����һָѸ�����磬ֱָ$nü�ģ�ָ���������ƺ�ͷ��̫�������У��ٻᣮ���ȸ���ҪѨ������һָ����";break;
                  
				   //default:break;
                }
				me->add_temp("yyz/yz3m",-1);
                if (level>=550) msg=RED+msg+NOR;
                else if (level>=450) msg = YEL + msg + NOR;
                else if (level>=350) msg = CYN + msg + NOR;
                return ([
                        "action":msg,
                        "damage_type":"����",
                        "dodge": 20,
				    	"damage":me->query("yideng/ronghe","pass")?(250+random(100)):(150+random(100)),
                        //"damage":200+random(50),
						"force": level + me->query("jiali"),
                        "skill_name" : "һָ������",
                        "weapon" : "һ��ָ��",
                ]);
        }
		//������,��Ҫ����ѧȫ����ʹ��
		 if( intp(n = me->query_temp("yyz/lmsj")) && n > 0 ){
               switch(n){
                   case 6: msglm =HIC"\n$N����Сָһ�죬ʹ�������󽣷�����һ�ɾ�����$P����Ѩ�м��������ָ����ǰ$n��\n"+
										 "$nֻ����һ�����ν��������$l�����������仯��΢������ޱȣ������Ǻ�����ȥ���仯��΢\n"NOR;break;
                   case 5: msglm =MAG"\n$N����ָһ�ӣ�׾�͹��ӵĹس彣��ֱ��������˶������ش���$n��$l,���ǡ��س彣����\n"+
									"$n�о��������ν���׾�͹��ӣ������б�ίʵ���Լܵ�,���ν�����Ȼʹ���޴Ӷ��\n"NOR;break;
                   case 4: msglm =HIG"\n$NĴָһ����ʳָ���������ˡ�������������һ�ƽ�����$n$l�̳���������Ѹ�٣������ޱ�\n"+
									"�����εĽ���������������ĥ���û���ֱ��$n������˲���ѱƵ���$��ǰ\n"NOR;break;

				   case 3: msglm =HIR"\n$N����һ����˫��ǰ�죬һʽ���г彣����,˫�ֺ�ʹ�����������ޱȵĽ����ƿմ���$n��$l\n"+
										"��Ȼ��$n�е������Ѩ����һ�ɴ󿪴�ϣ�������ΰ�����ν�������Χ\n"NOR;break;
                   case 2: msglm =CYN"\n$N��������ǰ�������Сָ��һ�С��ٳ彣����,�����ص���$n�������Ѩ����ָ��������ȴ��������\n"+
										"$n���ǽ������ý�ǰ�����Ǿ����������ƿ�֮������,���ν����ơ�׾������������������������������\n"NOR;break;
                   case 1: msglm =HIB"\n$N��Ĵָ��ǰ˫���������̽�����������һ����īɽˮ���ƣ��ݺ���б���������ʣ�ȴ�ǽ�·�۾�\n"+
									 "$n�������ν�������ʯ���쾪���������֮�ƣ��󿪴��أ����ɺ�ΰ�Ƶ�$n�ݸ߷��ͣ��������ܣ�\n"NOR;break;

				   default:break;
                }
                if (n>1) n-1;
                return ([
                        "action":msglm,
                        "damage_type":"����",
                        "dodge": 20,
				    	"damage":200+random(100),
						"force": level + me->query("jiali"),
                        "skill_name" : "������",
                        "weapon" : "���ν���",
                ]);
        }

 //  ####����#### �������ȥ����
        if ( stringp(msg = me->query("env/liumai")) 
        && me->query("jiali") > 50 
        && mapp(skill_name = me->query("liumai-shenjian")) 
        && me->query_skill("liumai-shenjian", 1) )
        {
                n = member_array(msg, keys(skill_name));
           if (sizeof(keys(skill_name))<2){
                if( n != -1 )
                        switch(msg){
                                case "shaoze": msg = shaoze[random(sizeof(shaoze))]; break;
                                case "guanchong": msg = guanchong[random(sizeof(guanchong))]; break;
                                case "shangyang": msg = shangyang[random(sizeof(shangyang))]; break;
                                case "shaochong": msg = shaochong[random(sizeof(shaochong))]; break;
                                case "zhongchong": msg = zhongchong[random(sizeof(zhongchong))]; break;
                                case "shaoshang": msg = shaoshang[random(sizeof(shaoshang))]; break;
                                default: msg = "";
                        }
                else msg = "";
           }
           else{
               if( n != -1 )
                   switch(msg){
                       case "shaoze": msg = shaoze[random(sizeof(shaoze))]; break;
                       case "guanchong": msg = guanchong[random(sizeof(guanchong))]; break;
                       case "shangyang": msg = shangyang[random(sizeof(shangyang))]; break;
                       case "shaochong": msg = shaochong[random(sizeof(shaochong))]; break;
                       case "zhongchong": msg = zhongchong[random(sizeof(zhongchong))]; break;
                       case "shaoshang": msg = shaoshang[random(sizeof(shaoshang))]; break;
                       default: msg = "";
                   }
               else if( n == -1 && msg == "shenjian") {
                   lmsj_msg = keys(me->query("liumai-shenjian"));
                   Gmsg = lmsj_msg[random(sizeof(lmsj_msg))];
                   switch(Gmsg){
                       case "shaoze": msg = shaoze[random(sizeof(shaoze))]; break;
                       case "guanchong": msg = guanchong[random(sizeof(guanchong))]; break;
                       case "shangyang": msg = shangyang[random(sizeof(shangyang))]; break;
                       case "shaochong": msg = shaochong[random(sizeof(shaochong))]; break;
                       case "zhongchong": msg = zhongchong[random(sizeof(zhongchong))]; break;
                       case "shaoshang": msg = shaoshang[random(sizeof(shaoshang))]; break;
                       default: msg = "";
                   }
               }
               else msg = "";
           }
                
            //hoho here is a bug,���jiali <50�Ļ������ʱ��msg����stringp,����set���Ǹ������ԼӸ��ж�:)
        	if( stringp(msg) && msg!=""){
                	me->set_temp("hit_ob_hit", 1);
                	me->set_temp("liumai_hit", me->query_str()*2);
                	
                	return ([
                        	"action": msg,
                        	"damage": 200+me->query_skill("liumai-shenjian", 1),
                        	"damage_type": "����",
                        	"dodge": random(me->query_dex()),
                        	"force": me->query_skill("force")/2 + me->query_str() * 5 + me->query("jiali") * 2,
                        	"parry": random(me->query_con()),
                        	"weapon" : "����",
                	]);
        	}
        }
     // ####һ��ָ####��ͨ���� 
        
		for(i = sizeof(action_finger); i > 0; i--)
                if(level >= action_finger[i-1]["lvl"])
			return action_finger[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{ 
        if ((int)me->query("jingli") < 70)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("�������������һ��ָ��\n");                         
        me->receive_damage("jingli", 40);
        me->receive_damage("neili", 10+random(10));
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yiyang-zhi/" + action;
}
int ob_hit(object ob, object me, int damage)
{
        string name,msg;
        int skill, neili, neili1, sh;
        int j = 0;
		skill = me->query_skill("yiyang-zhi", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");
        name = xue_name[random(sizeof(xue_name))];
/*
        if(me->query_temp("yiyang-zhi")){
                me->delete_temp("yiyang-zhi");
                return j;
        }
		*/
          	                  
        if(random(me->query_str(1)) > ob->query_dex(1)/2
         && random(me->query("combat_exp")) > ob->query("combat_exp")/2
         && me->query_skill_mapped("finger") == "yiyang-zhi"
         && neili > 2000 
         && skill > 350 
         && !me->query_temp("yiyang-zhi")
         && random(10) > 7){
         	    //me->add_temp("yiyang-zhi", 5);                 
                ob->receive_damage("qi", (damage>2000)?2000:damage , me);
                ob->receive_wound("qi", (damage>2000)?2000:damage , me);
              	j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              	message_vision(CYN "$N����$n���У�ָ��һתֱ��$n�ġ�"RED""+name+""CYN"����ȥ��$n���ܲ�������$Nһָ���С�\n"NOR,me,ob);
                msg = damage_msg(damage, "����") + "( $n"+eff_status_msg(j)+" )\n";
                j = -(damage*2+skill*3)/3;

				message_vision(msg, me, ob);
                return j;
          }
          else if(random(10) < 5 
                && !me->is_busy()
                && !ob->is_busy()  
                && me->query_skill_mapped("parry") == "yiyang-zhi"
                && !me->query_temp("yiyang-zhi")
                && me->query("neili")> ob->query("neili")
                  ){
          	        //me->add_temp("yiyang-zhi", 5);
                    ob->receive_damage("jing", (damage>800)?800:damage , me);
                    ob->receive_wound("jing", (damage>400)?400:damage , me);
              		ob->start_busy(2);
              		j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              		message_vision(BLU"$N����$n���У�ָ��һתֱ��$n�ġ�"HIW""+name+""BLU"����ȥ��$n��æ���ã����ƶ�ʱ���͡�\n"NOR,me,ob);
              		msg = damage_msg(damage, "����") + "( $n"+eff_status_msg(j)+" )\n";
              		message_vision(msg, me, ob);
                    j = -(damage*2+skill*3) /3;
 
				return j;
              } 
              	    
         // return j; 
        
          
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
       int hurt, lvl = me->query_skill("yiyang-zhi");
       int i, target_force, target_dodge, target_parry,j;
        string name,name2,liumai_set;
        object weapon = victim->query_temp("weapon");
        object *inv;
        name = xue_name[random(sizeof(xue_name))];
        name2 = xue_name[random(sizeof(xue_name))];
		
		i=me->query("yyz/degree");
        
		target_force = (int)victim->query_skill("force",1);
        target_dodge = (int)victim->query_skill("dodge",1);
        target_parry = (int)victim->query_skill("parry",1);
        if(me->query("env/liumai")) liumai_set = me->query("env/liumai");
       if( me->query_temp("yyz/yz3m")&&me->query("env/һ��ָ��Ѩ"))
		{
          switch(random(4)){
			case 0:
		      if((!me->query_temp("weapon")&&me->query("neili")>2000&& random(lvl+target_parry) > target_parry) 
              || random(me->query_skill("jingmai-xue")) > victim->query_skill("jingmai-xue") /2){
		          message_vision(HIW"$n����֪����һָ�������ľ��һ���мܲ��ܣ���"+HIR+name+HIW+"���ѱ����У���ʱ��Ϣ���ң�\n"NOR,me,victim);
                  if(!victim->query_condition("no_exert")) victim->apply_condition("no_exert",1+random(2));
				  else victim->add_condition("no_exert",1+random(2));
                  victim->add_condition("yyz_hurt",1+random(3));
				  }
				break;
			case 1:
             if(random(me->query("combat_exp"))> victim->query("combat_exp")/2)
	     	  {
                message_vision(HIC"$n��$N������һָ���������ֶ�����ʮ������Ѩ��ʵ�ڶ������㣬��"+HIR+name+HIC+"���ѱ����У�һ���ʹ�������̲�ס����һ����Ѫ��\n"NOR,me,victim);
                victim->receive_damage("jing", 2000,me);
				victim->receive_damage("qi", 2000,me);
                victim->add_condition("yyz_hurt",1+random(3));
		      }
			  break;
			case 2:
              message_vision(HIG"$n��$N������һָ������������������������һ�ţ���"+HIR+name+HIG+"���ѱ����У����ζ�ʱ���ƣ�\n"NOR,me,victim);
              if (victim->is_busy()) victim->add_busy(1+random(3));
              else victim->start_busy(1+random(3));
			  victim->add_condition("yyz_hurt",1+random(3));
			  break;
			case 3:
              if ((int)me->query("yyz/degree")<5)
              {             
			    message_vision(HIY"$Nһ��ָ��Ȼ����"+HIR+chinese_number(i)+"Ʒ"+HIY+"���磬����ʳָ��Ѩ����ָ�ɻ��ɿ죬��ʱ����Ʈ�ݣ����������磬����ָ֮�����ֺ����������"+HIR+name+HIY+"����ʹ��\n"NOR,me,victim);
                if (victim->is_busy()) victim->add_busy(1+random(3));
                else victim->start_busy(1+random(3));
				victim->receive_wound("jing",random(500),me);
				victim->add("jingli",-random(1000));
				victim->add_condition("yyz_hurt",1+random(3));
			  }
			  break;
		  }
		}
//������auto,Ҫ��������50
        if((int)me->query("jiali")>50
        && !me->query_temp("weapon") 
        && (int)me->query_skill("liumai-shenjian",1)>29
        && !me->query_temp("yyz/yz3m") ){
             //����Auto
            if((Gmsg =="shaoze"&&liumai_set=="shenjian" || liumai_set=="shaoze") && me->query("liumai-shenjian/shaoze")
            && random(lvl) > target_force/4 && random(2) ){
                message_vision(HIC"$N����΢΢һЦ,СĴָ��ɾ���ȥ�ľ���������Ϣ,$n�����޷����.\n"NOR,me,victim);
                message_vision(HIW"ͻȻ,$n�پ���"+HIR+name+HIW+"��һ��,ԭ���ѱ�$N��"CYN"������"HIW"����,��Ϣ��Ҳ�޷�����!\n"NOR,me,victim);
                //�����ƶԷ�����
				victim->receive_damage("qi",random(2000),me);
				message_vision(HIR"ͻȻ,$n�پ�ȫ��������к����!\n"NOR,me,victim);
				victim->add("neili",-random(2000));
				if(!victim->query_condition("no_exert")) victim->add_condition("no_exert",1+random(2));
					victim->add_condition("yyz_hurt",1+random(3));
					victim->add_busy(1);
            }
             //�ٳ�Auto
            else if((Gmsg=="shaochong"&&liumai_set=="shenjian"||liumai_set=="shaochong") && me->query("liumai-shenjian/shaochong")
            && random(lvl) > target_force/4){
                if (weapon){
					message_vision(HIG"$NСĴָ˳������һ��,��ʱһ���ƿ�֮��ֱ��$n����\n"NOR,me,victim);
					if(!random(4)||(me->query_temp("yyz/6mai/6mai")&&random(2))){
						message_vision(HIY"$n����Ϯ��һ���ѳֲ�ס��"+weapon->query("name")+HIY"���ֶ��������´󾪣���ʱ��æ���ң�\n"NOR,me,victim);
						weapon->unequip();
						weapon->move(environment(victim));
						victim->add_busy(2+random(3));
                }
                else{
                    message_vision(HIM"$nֻ������ھ���ͬС�ɣ���æ���б��˿�ȥ��\n"NOR,me,victim);
                    victim->add_temp("lost_attack", 1);
                }
                }
                else{
                    message_vision(HIB"$nֻ��һ�ɽ���Ϯ��,�����������,��æ����������һ�ߡ�\n"NOR,me,victim);
                    victim->add_temp("lost_attack", 1);
                }
            }
             //�س�Auto
            else if((Gmsg=="guanchong"&&liumai_set=="shenjian"||liumai_set=="guanchong") && me->query("liumai-shenjian/guanchong")
            && random(lvl) > target_force/4 && random(2) ){
                message_vision(HBRED"$N����ָһ������Ȼ����һ����������ʯ����������$n�ġ�"+HIW+name2+NOR+HBRED"����$n�پ���Ѫ���ڣ�����ɬ��!\n"NOR,me,victim);
                if(!victim->query_condition("no_perform")) victim->add_condition("no_perform",1+random(2));
                victim->add_condition("yyz_hurt",1+random(3));
				victim->receive_damage("qi",random(2000),me);

                victim->add_busy(1);
            }
             //�г�Auto
            else if((Gmsg=="zhongchong"&&liumai_set=="shenjian"||liumai_set=="zhongchong") && me->query("liumai-shenjian/zhongchong")
            && random(lvl) > target_dodge/4 ){
                message_vision(HIG"$N�����������������ڴ����У���ָ���������ׯ�أ��ھ�ʮ�㣡\n"NOR,me,victim);
                damage_bonus = damage_bonus/2;
                inv = filter_array(all_inventory(victim),(:$1->query("equipped")=="worn":));
                inv -= ({0});
                if((!random(3) ||( me->query_temp("yyz/6mai/6mai") && random(2)))&& sizeof(inv) >= 1){
                    for(i=0; i<(1+random(sizeof(inv))); i++){
                        inv[i]->unequip();
                        inv[i]->move(environment(victim));
                        inv[i]->set("name", "���ѵ�" + inv[i]->query("name"));
                        inv[i]->delete("value");
                        inv[i]->set("armor_prop", 0);
                    }
                    message_vision(HBBLU+HIC"�������������˸վ���������������$n�Ļ�����ߣ��㽫�������Ƭ���׷׵��䡣\n"NOR,me,victim);
                }
                return damage_bonus;
            }
             //����Auto
            else if((Gmsg=="shangyang"&&liumai_set=="shenjian"||liumai_set=="shangyang") && me->query("liumai-shenjian/shangyang") ){
            if ( random(lvl) > target_parry/4 ){
                if(!me->query_temp("yyz/6mai/shangyang") && random(2) ){
                    message_vision(HIC"$Nһָ�����������ж��֣�ʳָ�ٿ�������£�$n�پ�������������Ϯ����\n"NOR,me,victim);
                    me->set_temp("yyz/6mai/shangyang",1);
                    call_out("liumai_shangyang",0,me,victim,lvl);
                }
                else{
                    if(me->query_temp("yyz/6mai/shangyang")) me->delete_temp("yyz/6mai/shangyang");
                    message_vision(HIB"$NǱ���������������ƴ�����\n"NOR,me,victim);
                }
            }
            else message_vision(HIB"$NǱ���������������ƴ�����\n"NOR,me,victim);
            }
             //����Auto
            else if((Gmsg=="shaoshang"&&liumai_set=="shenjian"||liumai_set=="shaoshang") && me->query("liumai-shenjian/shaoshang")
            && random(lvl) > target_parry/3 ){
                message_vision(HIR"$N��ɫ���أ������ھ�����Ĵָһָ�����ɲ�Ǽ䣬һ�ɺ��������Ľ���ֱ��$n,����ʵ�˺��ˣ�\n"NOR,me,victim);
                victim->receive_damage("qi",random(2000),me);
				victim->add_condition("yyz_hurt",1+random(3));
                return damage_bonus*2;
            }
        }

        if(me->query_temp("autopfm_yyz")){
                me->delete_temp("autopfm_yyz");
                return 0;
        }
        
        if( me->is_perform() 
        || !me->query("env/һ��ָ��Ѩ")
        || me->query("neili") < 1000
	    || me->query("max_neili") < 1500
        || me->query_skill("yiyang-zhi", 1) < 150 
        //|| me->query_temp("yyz/yz3m")
			)
        	return 0;       

        
        if ( lvl > 300) lvl = 300 + (lvl-300)/10;
        
        if (random(10) > 6
        && !me->query_temp("yyz/yz3m")
        && me->query_skill_prepared("finger") == "yiyang-zhi"
        && me->query("combat_exp") >= (victim->query("combat_exp")/3*2) ){
          	
                if (me->query("env/liumai")
                && me->query_temp("liumai_hit")
                && !me->query_temp("autopfm_yyz")
                && !victim->is_busy()
                && !objectp(weapon = me->query_temp("weapon"))
                && me->query("jiali") > 50  
                && random(10) > 3
                
                ){
                        if (me->query("neili") > 40)
                                me->add("neili", -40);
                        else	me->set("neili", 0);
                        hurt = (victim->query("neili") < lvl / 6 ? victim->query("neili") : lvl / 6);
                        victim->add("neili", -hurt/2);
                        victim->receive_wound("qi", -lvl / 6);
                        victim->add("jingli", -lvl / 6);
                        me->add_temp("autopfm_yyz",2);
                        me->delete_temp("liumai_hit");
                        victim->start_busy(2+random(2));    
                        return HBRED "��ʯ����$Nָ��һת,ָ����Я��һ�������������$n,\n"+
                                     "$n��$Nһָ���С�"+name+HBRED"��������������һ�ͣ�����΢΢һ����\n" NOR;
                } 
                return 0;
        } 
        else if (lvl > 150 
        && random(10) > 3
        && !victim->query_temp("yyz")
        && !me->query_temp("autopfm_yyz")
        ) { if(me->query_temp("liumai_hit")){
                me->delete_temp("liumai_hit");
                return 0;
        } else {
            	switch (random(3)) {
               		case 0: 
                    		if (weapon){
                       			weapon->unwield();
                       			weapon->move(environment(victim));
                       			victim->add("neili", -lvl/5);
                       			
                       			me->set_temp("autopfm_yyz",3);
                       			return CYN "$N����һָ,��һ�б仯Ī��,������$n�ġ�"HIR+name+CYN"����\n"NOR+
                       			       CYN "$n��һ�飬"+weapon->query("name")+CYN"�ѳֲ�ס�����ڵ��ϡ�\n" NOR; 
                       		} 
                       		else {
                       			victim->add("neili", -lvl*4);
                       			victim->add_busy(1);
                       			me->set_temp("autopfm_yyz",1);
                       			return CYN "$N����һָ,��һ�б仯Ī��,������$n�ġ�"HIR+name+CYN"����\n"NOR+
                       			       YEL "������$Nʳָһ��һ��,һ��ָ���ƿն���,������$n�ġ�"RED""+name2+""YEL"����$n���������̻�ɢ��\n" NOR; 
                       		}
                       		break;
               		case 1: 
               			victim->start_busy(2+random(2));
               			
               			me->set_temp("autopfm_yyz",3);
                    		return CYN "$N��ָ���,ɲ�Ǽ�����һ��ָ��ֱ��$n�ġ�"HIR+name+CYN"����$n����һ��,������ҪѨ��\n" NOR;
                    		break;
               		case 2: 
               			victim->apply_condition("no_perform", 2+random(2));
               			victim->apply_condition("no_exert",1+random(2));
               			
               			me->set_temp("autopfm_yyz",3);
                    		return CYN "$Nһָ���,����$n�ġ�"HIR+name+CYN"����һ��ָ�ھ�ֱ͸��$n���ڸ���ҪѨ��\n" NOR;
                    		break;
            	}
        }
}

}

int liumai_shangyang(object me, object target, int lvl)
{
    int i;
    if(me->query("env/liumai")
    && objectp(me)
    && objectp(target)
	&& me->query("env/liumai")=="shangyang"
    && me->query("liumai-shenjian/shangyang")
    && me->is_fighting()
    && (int)me->query("jiali")>50
    && !me->query_temp("weapon")
    && me->query_skill_prepared("finger") == "yiyang-zhi"
    && me->query_skill_mapped("finger") == "yiyang-zhi" ){
      message_vision(HIW"$N���Ǽ��ɽ���ɲ�Ǽ��Ѿ�Ϯ��$n��ǰ��ֱ��$n�����æ���ң�\n"NOR,me,target);
	  if (target) target->add_busy(2);
      me->set_temp("yyz/6mai/shangyang",1);
      if(me->query_temp("yyz/6mai/6mai")){
          me->add_temp("apply/attack",lvl/4);
          me->add_temp("apply/dodge",lvl/4);
      }
      for(i=0;i<(2+random(2));i++){
        if (lvl>500) COMBAT_D->do_attack(me, target, 0, 3);
        else COMBAT_D->do_attack(me, target, 0, 1);
      }
      if(me->query_temp("yyz/6mai/6mai")){
          me->add_temp("apply/attack",-lvl/4);
          me->add_temp("apply/dodge",-lvl/4);
      }
    }
    return 1;
}
