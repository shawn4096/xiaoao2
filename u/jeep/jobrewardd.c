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
#define BASEEXP 60
//ȫ�ֶ���PVP��������������齱��.
#define PVPEXP 180

//ȫ�ֶ����޶����������EXP����Ϊ75M
#define LIMITEXP 75000000

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
	int exp, expquo, pot, shen,exprelife,t;
	object ebook;
	string msg;

    msg = HIW"��ϲ�㣡��ɹ��������" + job + "�����㱻�����ˣ�\n" + NOR;

	//�������PVP���ͣ���������齱��ȡȫ�ֶ��壬����ȡPVP��ֵ��
	if(!PVPquo){

		//����ֵ����
		//0-5m��1.5����������
		//5m-15m��1.2���٣�
		//��0-15M��ʼ������Ϊ���ٳɳ���*1.5 
		//15-28MΪƽ���ٶ�*1 (��Ϊ�в�������)
		//28-35Ϊ������*0.8 (��վ��,���ư�)
		//35�Ժ�����ĥ��(����4������)
		//�ƻ����½��������ٶȣ�̫���˲���
		// 28mǰ��ȫ���������������ٶ�
		// 28��35֮��Ϊ80%���ٷ�չ
		// 35��75֮��Ϊ50%������
		// 75m��ֹͣ����

		if (obj->query("combat_exp") < 5000000) exp = BASEEXP;
		if (obj->query("combat_exp") >= 5000000 && obj->query("combat_exp") <= 15000000) exp = BASEEXP;
		if (obj->query("combat_exp") >= 15000000 && obj->query("combat_exp") <= 25000000) exp = BASEEXP ;
		if (obj->query("combat_exp") > 25000000 && obj->query("combat_exp") <= 35000000) exp = BASEEXP * 0.7;
		if (obj->query("combat_exp") > 35000000) exp = BASEEXP * 0.5;
		if (obj->query("combat_exp") > 75000000) exp = BASEEXP * 0;

		//ϴ�ֳͷ�20%
		if(obj->query("no_pk")) exp = exp * 0.8;

		//if(hardquo > 20) hardquo = 20;
		if(hardquo < -10) hardquo = -10;
		switch (job)
		{
			case "�䵱":
				exp = exp;
				break;
			case "ѩɽ":
				exp = 1.1 * exp;
				break;
			case "��ػ�":
				exp = 1.4 * exp;
				break;
			default:
				exp = exp;
				break;
		}
      
		if(hardquo >= 0)
			exp = exp + exp * hardquo * 3/20 + random(exp * hardquo /20);
		else
			exp = exp + exp * hardquo * 3/20 - random(-1 * exp * hardquo /20);

		if(hardquo == -10)
			exp = 0;

		if(hardquo > 25)   
			exp = exp * 1.5;
		else if(hardquo > 20)
			exp = exp * 1.2;
	}
	else{
		//���鲿��
		exp = PVPEXP;
		if(PVPquo > 10) PVPquo = 10;
		if(PVPquo < 0) PVPquo = 0;
		exp = exp + exp * PVPquo / 10 + random(50);  //������������־��飬����������Ӯ���μӵ��˶��С�
		exp = exp + (exp - PVPEXP) * PVPquo * PVPlvl;  //������⽱�����֣�Ҳ���ǻ��PVPlvlԽ�࣬����Խ�ࡣ
	}

	//�鿴EXP�Ƿ񳬱�
	if(maxexp != 0 && exp > maxexp)
		exp = maxexp + random(maxexp/10);

	//��ͨ�¿�VIPplayer�ӳ�
	if(obj->query("registered") == 3)
		exp = exp + exp * VIPQUO * 1 / 20;

	//�꿨VIPplayer�ӳ�,���Ϊy-card-vip
	if(obj->query("y-card-vip"))
		exp = exp + exp * VIPQUO * 1 / 20;

	//����vip���� ���Ϊbuyvip
	if(obj->query("buyvip") )
		exp = exp + exp * VIPQUO * 1/ 10;

	//���ռӳɲ��֡�
	exp = exp + exp * FESTIVAL / 10;

	//������ѧ�ľ����ȡ���֣����޵���20�㡣
	if(obj->query("relife/exp_ext")){
		exprelife = exp * (int)obj->query("relife/exp_ext",1) / 20;
	}

	//�޶����EXP�������޺󣬼���̶ȵؽ��;��齱����
	if(obj->query("combat_exp") > LIMITEXP){
		exp =  exp * 5 /100;
		tell_object(obj,"������Լ����������������ѧ���о��Ѿ������˾ٲ�Ω��ĳ̶ȣ��ƺ����ǽ�����˵�ġ�"+HIG+"��ѧ��"+NOR+"����\n");
	}

	msg += HIW + chinese_number(exp) + "�㾭��!\n" + NOR;

	//Ǳ�ܲ���
	//pot = exp / 3;
	pot = exp * 3/20 + random(exp/20);

	if(hardquo == -10)
		pot = maxexp;

	msg += HIW + chinese_number(pot) + "��Ǳ��!\n" + NOR;

	//shen����
	if(shenflag == 1){
		//shen = exp / 2 + random(exp / 6);
		shen = 10 + random(10);
		msg += HIW + chinese_number(shen) + "������\n" + NOR;
	}
	else if(shenflag == -1){
		// shen = - exp / 2 - random(exp / 6);
		shen = - 10 - random(10);
		msg += HIW + chinese_number(-shen) + "�㸺��\n" + NOR;
	}
	else shen = 0;

	//ͨ������
	if(credit < 0) credit = random(exp / 100);
	if(credit > 3) credit = 3;//����ͨ����		
	if(credit != 0) msg += HIW + chinese_number(credit) + "��ͨ����\n" + NOR;

	//���ⲿ�֣�˫������
	expquo = 0;
	if(obj->query_condition("db_exp")){  // ˫������
		expquo = exp;
		msg += HIY + "˫�����齱���ڼ䣬�����صõ���" + chinese_number(expquo) + "�㾭�飡\n" + NOR;
	}

	//������ѧEXP�ӳɵ�����
	if(obj->query("relife/exp_ext")) 
		msg += HBYEL + "�㾲����������������ղŵ�������̣�������Ȼ���ʡ��������صõ���" + chinese_number(exprelife) + "�㾭�飡\n\n" + NOR;

	obj->add("combat_exp",exp + exprelife + expquo);
	obj->add("potential",pot);

	if(potflag != 1 && obj->query("potential") > obj->query("max_pot") && !obj->query("relife/times"))
		obj->set("potential",obj->query("max_pot"));

	if(obj->query("relife/times") && obj->query("potential") > LIMITPOT * (int)obj->query("relife/times"))
		obj->set("potential",LIMITPOT * (int)obj->query("relife/times"));

	obj->add("shen",shen);
	obj->add("SJ_Credit",credit);
	obj->add("job_time/"+job, 1);
	tell_object(obj,msg);

	//log_file( "jobreward/"+job,sprintf("%s(%s)�ɹ���ɵ�%d��%s����,��� EXP:%d, EXPQUO:%d, POT:%d, SHEN:%d, 
	//CREDIT:%d"NOR,obj->name(),obj->query("id"),obj->query("job_time/"+job),job,exp,expquo,pot,shen,credit));

	//����ebook���Ѷȣ���30000����60000����ֹ���죬��Ҳ��ϡȱ��Դ��
	if( random(30000) == 100
	&& random(500) < ( obj->query("int") + obj->query("str") + obj->query("dex") + obj->query("con") )
	//&& obj->query("combat_exp",1) >= 150000 && (obj->query("y-card-vip") || obj->query("buyvip")|| obj->query("m-card-vip")))
	&& obj->query("combat_exp",1) >= 150000 && (obj->query("y-card-vip") || obj->query("buyvip") ))
	{
		tell_object(obj, HIW"�����߽�����������𣬶Ը��صķ�������ż�����ã����ɵ�����һ˿����ļ��⡣������һ��"HIY"��Ӣ֮��"HIW"��\n"NOR);
		ebook = new("/u/jpei/ebook");
		ebook->move(obj);
		log_file("jobreward/ebook",sprintf("%s(%s)�ɹ���ɵ�%d��%s����ʱ���һ����Ӣ֮�飡\n"NOR,obj->name(),obj->query("id"),obj->query("job_time/"+job),job));
	}

	if(giver)
		GIFT_D->check_count(obj,giver,job,0);
	return 1;
}
