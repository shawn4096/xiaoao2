// ͳһ����������������by lsxk  2008/1/7
// By Spiderii@ty �Ӹ�������ϴ�ֵ�JOB�����Ȳ�ϴ�ֵĽ���һЩ
// By Spiderii@ty ת�����pot���޵����ơ����̼����ת��
// update by lsxk@hsbbs 2008/06/27 ���ת�����Ǳ�������޶�
// Update by Jpei@feixue �ſ�hardquo���޸���������������vip��ʶ��


/* ����˵����
    obj:    �������
    job:    ��������
    shenflag:    �������־,����Ϊ1������Ϊ-1����������Ϊ0.
    potflag:    Ǳ�ܱ�־������1��Ǳ�ܳ����޸������򲻳����ޡ�
    credit:    ͨ����־��0Ϊ��ͨ��������-1Ϊ��ϵͳ���ݾ���ֵ��������ͨ��������������ֵΪָ��ͨ��������ֵ.
    hardquo:    �Ѷ�ϵ������ֵ��-10��20����ֵԽ�ߣ�˵���Ѷȸߣ����Խ����ࡣ������ʱ�򣬽�������С�ڻ���������-10,���齱��Ϊ0������maxexp������Ǳ�ܡ�
    PVPquo:    �Ƿ������VS������͵����񣬼������������ǣ����봫�ݸ�PVP�������ӳ�ϵ��(1-10)������Ϊ0.
    PVPlvl:    PVP�����������ȼ��������������񣺳ɹ�ɱ��3���Է����ˣ������ֵ����3���������ǡ�
    maxexp:    ���EXP��ֵ��������������EXP���������������ȡ���ֵ���ڼ���ӳɽ���֮ǰ��Ч��Ϊ0�����ơ�
    giver:    ˭���Ľ������������GIFT_D�������������
*/

//ȫ�ֶ����������ֵ����
#define BASEEXP 50
//ȫ�ֶ���PVP��������������齱��.
#define PVPEXP 180

//ȫ�ֶ����޶����������EXP����Ϊ7500M
#define LIMITEXP 7500000000

//ȫ�ֶ���ת�����Ǳ�ܽ�����������Ϊ50000��
#define LIMITPOT 50000

//����VIP Player�Ľ����ӳ�ϵ����ע����㷽ʽΪ��exp + exp * VIP�����ӳ�ϵ�� / 100
#define VIPQUO 1

//������ս����ӳɲ�����ע����㷽ʽΪ��exp + exp * ���ռӳ�ϵ�� / 10 
#define FESTIVAL 1

//�����Խ�ɽׯ���뽱�������EXP���ơ�
#define ENTER_MIN_EXP 2000000

#include <ansi.h>;

int get_reward(object obj, string job, int shenflag, int potflag, int credit, int hardquo, int PVPquo, int PVPlvl, int maxexp, mixed giver)
{
    int exp,vipexp,expquo, pot, shen,exprelife,t;
	int a;
    object ebook;
    string msg;
   


    msg = HIR"��ϲ�㣡��ɹ��������" + HIG + job + HIR + "�����㱻�����ˣ�\n" + NOR;

//�������PVP���ͣ���������齱��ȡȫ�ֶ��壬����ȡPVP��ֵ��
    if(!PVPquo){

//����ֵ����
// 25mǰ��ȫ���������������ٶ�
// 25��35֮��Ϊ50%���ٷ�չ
// 35��75֮��Ϊ20%������
// 75m��ֹͣ����
// ��ϴ����0.8���ͷ�


if (obj->query("combat_exp")<5000000) exp = BASEEXP;
if (obj->query("combat_exp")>=5000000 && obj->query("combat_exp")<=15000000) exp = BASEEXP;
if (obj->query("combat_exp")>=15000000 && obj->query("combat_exp")<=25000000) exp = BASEEXP;
if (obj->query("combat_exp")>25000000 && obj->query("combat_exp")<=35000000) exp = BASEEXP * 0.5;
if (obj->query("combat_exp")>35000000) exp = BASEEXP * 0.5;
//if (obj->query("combat_exp")>75000000) exp = BASEEXP * 0;
//ϴ�ֳͷ�20%
//ȡ��ϴ�ֳͷ�
       //if(obj->query("no_pk")) exp = exp * 0.8;

        if(obj->query("no_pk")) a=30000;
		else a=10000;
        
        //if(hardquo > 20) hardquo = 20;
		if(hardquo < -10) hardquo = -10;
         switch (job)
         {
           case "�䵱":
		   case "������ͽ":
		       exp=exp;
		       break;
		   case "ѩɽ":
			   exp=1.1*exp;
		       break;
		   case "���¸���":
			   exp=1.2*exp;
		       break;
		   case "��ػ�":
               exp=1.4*exp;
		       break;
		   default:
			   exp=exp;
		       break;
          }
      
        if(hardquo >= 0)
            exp = exp + exp * hardquo /10 + (random(exp)+1) * hardquo /10;
        else
            exp = exp + exp * hardquo /10 - random( -1 * exp * hardquo /10);

        if(hardquo == -10)
            exp = 0;
        if(hardquo > 20)   
           exp = exp * 1.5; //2.5 �ĳ� 1.5
    }
    else{

//���鲿��
        exp = PVPEXP;
        if(PVPquo > 10) PVPquo = 10;
        if(PVPquo < 0) PVPquo = 0;
        exp = exp + exp * PVPquo / 10 + random(50);  //������������־��飬����������Ӯ���μӵ��˶��С�
        exp = exp + (exp - PVPEXP) * PVPquo * PVPlvl;  //������⽱�����֣�Ҳ���ǻ��PVPlvlԽ�࣬����Խ�ࡣ
    }


// ���ռӳɲ��֡�
            exp = exp + exp * FESTIVAL / 10;

//������ѧ�ľ����ȡ���֣����޵���20�㡣
        
        
		
//�鿴EXP�Ƿ񳬱�
        if(maxexp != 0 && exp > maxexp)
            exp = maxexp + random(maxexp/10);

		
//�����vip����	
       vipexp=0;
	   
		if(obj->query("buyvip") )
            vipexp = exp * VIPQUO * 20/ 100;
		else if(obj->query("y-card-vip"))
            vipexp =exp * VIPQUO * 10 / 100;
		else if(obj->query("m-card-vip"))
			//vipexp=0;
            vipexp =exp * VIPQUO * 1 / 100;
			//��Ϊ�¿��Ǳ��䣬�����¿���������
	   exp=exp+vipexp;
	   
//was�����ۼ� ����������10��100 20��400��
		exp=exp+PVPlvl*PVPlvl;
		
	if(obj->query("relife/exp_ext")){
           exprelife=exp*(int)obj->query("relife/exp_ext",1) / 20;
        }

// �޶����EXP�������޺󣬼���̶ȵؽ��;��齱����
        if(obj->query("combat_exp") > LIMITEXP){
            exp =  exp * 5 /100;
            tell_object(obj,"������Լ����������������ѧ���о��Ѿ������˾ٲ�Ω��ĳ̶ȣ��ƺ����ǽ�����˵�ġ�"+HIG+"��ѧ��"+NOR+"����\n");
        }

        msg += HIW + chinese_number(exp) + HIC + "��" + HIM + "����!\n"NOR;

//Ǳ�ܲ���
        //pot = exp / 3;
		pot=100+random(50);

        if(hardquo == -10)
            pot = maxexp;

        msg += HIW + chinese_number(pot) + HIC + "��" + HIY + "Ǳ��!\n"NOR;



//shen����
        if(shenflag==1){
            //shen = exp / 2 + random(exp / 6);
			shen = 20 + random(10);
            msg += HIW + chinese_number(shen) + HIC + "������\n"NOR;
        }
        else if(shenflag == -1){
           // shen = - exp / 2 - random(exp / 6);
			shen = - 50 - random(10);
            msg += HIW + chinese_number(-shen) + HIC + "��" + HIR + "����\n"NOR;
        }
		else if(shenflag == 2){
           // shen = - exp / 2 - random(exp / 6);
		    if (PVPlvl>11) shen = 2000 + random(1000);
			else shen=50 + random(100);
            msg += HIW + chinese_number(shen) + HIC + "��" + HIR + "����\n"NOR;
        }
        else shen = 0;

//ͨ������
/*
        if(credit < 0) credit = random(exp / 100);
		if (credit>1 && !obj->query("no_pk")) credit=1+random(1);//����ͨ����,ֻ�з�ϴ����ҿ��Ի��		
        if(credit != 0) msg += HIW + chinese_number(credit) + HIC + "��" + HIW + "ͨ����\n"NOR;
*/
//���ⲿ�֣�˫������
		credit=0; //�趨����tbΪ0
        
		expquo = 0;
        if(obj->query_condition("db_exp")){  // ˫������
            expquo = exp;
            msg += HIY + "˫�����齱���ڼ䣬�����صõ���" + HIW + chinese_number(expquo) + HIC + "��" + HIM + "���飡\n"NOR;
        }

//������ѧEXP�ӳɵ�����
       if(obj->query("relife/exp_ext")) 
        msg += HBYEL + "�㾲����������������ղŵ�������̣�������Ȼ���ʡ��������صõ���" + HIW + chinese_number(exprelife) + HIC + "��" + HIM + "���飡\n\n"NOR;
   
      
	   obj->add("shen",shen);
       obj->add("combat_exp",exp+exprelife+expquo);
       obj->add("potential",pot);

    if(potflag != 1 && obj->query("potential") > obj->query("max_pot") && !obj->query("relife/times"))
       obj->set("potential",obj->query("max_pot"));

    if(obj->query("relife/times") && obj->query("potential") > LIMITPOT * (int)obj->query("relife/times"))
       obj->set("potential",LIMITPOT * (int)obj->query("relife/times"));
      
     //  obj->add("SJ_Credit",credit);
       obj->add("job_time/"+job, 1);
	   //���ӵ�ǰ����Ĺ�������
	   obj->set("job_name",job);

       tell_object(obj,msg);
	   

//180:     log_file( "jobreward/"+job,sprintf("%s(%s)�ɹ���ɵ�%d��%s����,��� EXP:%d, EXPQUO:%d, POT:%d, SHEN:%d, CREDIT:%d"NOR,obj->name(),obj->query("id"),obj->query("job_time/"+job),job,exp,expquo,pot,shen,credit));
    
    //����ebook���Ѷȣ���30000����60000����ֹ���죬��Ҳ��ϡȱ��Դ��
       if( random(a) == 100
        && random(500) < ( obj->query("int") + obj->query("str") + obj->query("dex") + obj->query("con") )
        && obj->query("combat_exp",1) >= ENTER_MIN_EXP && (obj->query("y-card-vip") || obj->query("buyvip") ))
   	{
    
       //tell_object(obj, HIW"�����߽������Ը��صķ�������ż�����ã����ɵ�����һ˿����ļ��⡣������һ��"HIY"�Խ�ɽׯ����"HIW"��\n"NOR);	   
	   if (!obj->query("no_pk")&& !random(20))
	   {
		   tell_object(obj, HIY"��������ɱ����Ȼ��һ������ɱ������֮����������һЩ�ƽ�\n"NOR);
		   new("clone/money/gold")->move(obj);
	   }
       ebook=new("/d/sjsz/obj/sjsz_ling");
       ebook->move(obj);
	   //CHANNEL_D->do_channel(this_object(), "rumor",sprintf("���˿���%sŪ����һö%s��", obj->name(1), ebook->query("name")));
       log_file("jobreward/ebook",sprintf("%s(%s)�ɹ���ɵ�%d��%s����ʱ���һ���Խ�ɽׯ���ƣ�\n"NOR,obj->name(),obj->query("id"),obj->query("job_time/"+job),job));
    }

    if(giver)
        GIFT_D->check_count(obj,giver,job,0);
    return 1;
}
