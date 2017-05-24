/**
 * Haar Cascade
 * Usage: HaarCascadeFrontalFaceAlt();
 */

precision highp float;

varying vec2 v_texcoord;
uniform sampler2D ii;
uniform sampler2D ii2;
uniform float invArea;
uniform float iiMax;
uniform float ii2Max;
uniform float scale;
uniform vec2 pixelSizeIn;

float sample_ii(vec2 coord)
{
	vec4 value = texture2D(ii, coord);
	float r = value.r * 255.0;
	float g = value.g * 255.0;
	float b = value.b * 255.0;
	return (b * 65536.0 + g * 256.0 + r) / 16777215.0 * iiMax;
}

float rect_sum_ii(float x, float y, float w, float h, float weight)
{
	vec2 topLeft = v_texcoord + vec2(x * scale * pixelSizeIn.x, y * scale * pixelSizeIn.y);
	vec2 topRight = topLeft + vec2(w * scale * pixelSizeIn.x, 0.0);
	vec2 bottomLeft = topLeft + vec2(0.0, h * scale * pixelSizeIn.y);
	vec2 bottomRight = bottomLeft + vec2(w * scale * pixelSizeIn.x, 0.0);

	return weight * (sample_ii(bottomRight) + 
		sample_ii(topLeft) - sample_ii(topRight) - sample_ii(bottomLeft));
}

float sample_ii2(vec2 coord)
{
	vec4 value = texture2D(ii2, coord);
	float r = value.r * 255.0;
	float g = value.g * 255.0;
	float b = value.b * 255.0;
	return (b * 65536.0 + g * 256.0 + r) / 16777215.0 * ii2Max;
}

float rect_sum_ii2(float x, float y, float w, float h, float weight)
{
	vec2 topLeft = v_texcoord + vec2(x * scale * pixelSizeIn.x, y * scale * pixelSizeIn.y);
	vec2 topRight = topLeft + vec2(w * scale * pixelSizeIn.x, 0.0);
	vec2 bottomLeft = topLeft + vec2(0.0, h * scale * pixelSizeIn.y);
	vec2 bottomRight = bottomLeft + vec2(w * scale * pixelSizeIn.x, 0.0);

	return weight * (sample_ii2(bottomRight) + 
		sample_ii2(topLeft) - sample_ii2(topRight) - sample_ii2(bottomLeft));
}

int HaarCascadeFrontalFaceAlt_stage0(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 7.0, 14.0, 4.0, -1.0);
	sum += rect_sum_ii(3.0, 9.0, 14.0, 2.0, 2.0);
	if(sum < 0.004014195874333382 * factor)
		stage_sum += 0.03379419073462486;
	else
		stage_sum += 0.8378106951713562;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 2.0, 18.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 2.0, 6.0, 4.0, 3.0);
	if(sum < 0.015151339583098888 * factor)
		stage_sum += 0.1514132022857666;
	else
		stage_sum += 0.7488812208175659;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 15.0, 9.0, -1.0);
	sum += rect_sum_ii(1.0, 10.0, 15.0, 3.0, 3.0);
	if(sum < 0.004210993181914091 * factor)
		stage_sum += 0.09004928171634674;
	else
		stage_sum += 0.6374819874763489;


	if(stage_sum > 0.822689414024353)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage1(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 9.0, 2.0, 3.0, 2.0);
	if(sum < 0.0016227109590545297 * factor)
		stage_sum += 0.06930858641862869;
	else
		stage_sum += 0.7110946178436279;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 5.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 2.0, 3.0, 3.0);
	if(sum < 0.002290664939209819 * factor)
		stage_sum += 0.17958030104637146;
	else
		stage_sum += 0.6668692231178284;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 0.0, 12.0, 9.0, -1.0);
	sum += rect_sum_ii(4.0, 3.0, 12.0, 3.0, 3.0);
	if(sum < 0.005002570804208517 * factor)
		stage_sum += 0.16936729848384857;
	else
		stage_sum += 0.6554006934165955;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 9.0, 10.0, 8.0, -1.0);
	sum += rect_sum_ii(6.0, 13.0, 10.0, 4.0, 2.0);
	if(sum < 0.007965989410877228 * factor)
		stage_sum += 0.5866332054138184;
	else
		stage_sum += 0.09141451865434647;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 6.0, 14.0, 8.0, -1.0);
	sum += rect_sum_ii(3.0, 10.0, 14.0, 4.0, 2.0);
	if(sum < -0.003522701095789671 * factor)
		stage_sum += 0.14131669700145721;
	else
		stage_sum += 0.6031895875930786;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 1.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(14.0, 1.0, 3.0, 10.0, 2.0);
	if(sum < 0.03666768968105316 * factor)
		stage_sum += 0.3675672113895416;
	else
		stage_sum += 0.7920318245887756;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 5.0, 12.0, -1.0);
	sum += rect_sum_ii(7.0, 12.0, 5.0, 4.0, 3.0);
	if(sum < 0.009336147457361221 * factor)
		stage_sum += 0.6161385774612427;
	else
		stage_sum += 0.20885099470615387;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 1.0, 18.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 1.0, 6.0, 3.0, 3.0);
	if(sum < 0.008696131408214569 * factor)
		stage_sum += 0.2836230993270874;
	else
		stage_sum += 0.6360273957252502;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 8.0, 17.0, 2.0, -1.0);
	sum += rect_sum_ii(1.0, 9.0, 17.0, 1.0, 2.0);
	if(sum < 0.0011488880263641477 * factor)
		stage_sum += 0.2223580926656723;
	else
		stage_sum += 0.5800700783729553;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 6.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 7.0, 4.0, 1.0, 2.0);
	if(sum < -0.002148468978703022 * factor)
		stage_sum += 0.24064640700817108;
	else
		stage_sum += 0.5787054896354675;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 17.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 18.0, 2.0, 1.0, 2.0);
	if(sum < 0.002121906029060483 * factor)
		stage_sum += 0.5559654831886292;
	else
		stage_sum += 0.136223703622818;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 2.0, 6.0, 12.0, -1.0);
	sum += rect_sum_ii(14.0, 2.0, 3.0, 12.0, 2.0);
	if(sum < -0.09394914656877518 * factor)
		stage_sum += 0.8502737283706665;
	else
		stage_sum += 0.47177401185035706;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 0.0, 4.0, 12.0, -1.0);
	sum += rect_sum_ii(4.0, 0.0, 2.0, 6.0, 2.0);
	sum += rect_sum_ii(6.0, 6.0, 2.0, 6.0, 2.0);
	if(sum < 0.0013777789426967502 * factor)
		stage_sum += 0.5993673801422119;
	else
		stage_sum += 0.28345298767089844;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 11.0, 18.0, 8.0, -1.0);
	sum += rect_sum_ii(8.0, 11.0, 6.0, 8.0, 3.0);
	if(sum < 0.07306315749883652 * factor)
		stage_sum += 0.4341886043548584;
	else
		stage_sum += 0.7060034275054932;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 10.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 8.0, 10.0, 1.0, 2.0);
	if(sum < 0.00036767389974556863 * factor)
		stage_sum += 0.30278879404067993;
	else
		stage_sum += 0.6051574945449829;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 11.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 12.0, 5.0, 1.0, 3.0);
	if(sum < -0.0060479710809886456 * factor)
		stage_sum += 0.17984339594841003;
	else
		stage_sum += 0.5675256848335266;


	if(stage_sum > 6.956608772277832)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage2(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 3.0, 10.0, 9.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 10.0, 3.0, 3.0);
	if(sum < -0.01651068963110447 * factor)
		stage_sum += 0.6644225120544434;
	else
		stage_sum += 0.14248579740524292;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 4.0, 2.0, 14.0, -1.0);
	sum += rect_sum_ii(9.0, 11.0, 2.0, 7.0, 2.0);
	if(sum < 0.002705249935388565 * factor)
		stage_sum += 0.6325352191925049;
	else
		stage_sum += 0.12884770333766937;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 5.0, 4.0, 12.0, -1.0);
	sum += rect_sum_ii(3.0, 9.0, 4.0, 4.0, 3.0);
	if(sum < 0.002806986914947629 * factor)
		stage_sum += 0.12402880191802979;
	else
		stage_sum += 0.6193193197250366;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 5.0, 12.0, 5.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 4.0, 5.0, 3.0);
	if(sum < -0.0015402400167658925 * factor)
		stage_sum += 0.14321430027484894;
	else
		stage_sum += 0.5670015811920166;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 10.0, 8.0, -1.0);
	sum += rect_sum_ii(5.0, 10.0, 10.0, 4.0, 2.0);
	if(sum < -0.0005638627917505801 * factor)
		stage_sum += 0.16574330627918243;
	else
		stage_sum += 0.5905207991600037;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 0.0, 6.0, 9.0, -1.0);
	sum += rect_sum_ii(8.0, 3.0, 6.0, 3.0, 3.0);
	if(sum < 0.0019253729842603207 * factor)
		stage_sum += 0.26955071091651917;
	else
		stage_sum += 0.5738824009895325;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 12.0, 1.0, 8.0, -1.0);
	sum += rect_sum_ii(9.0, 16.0, 1.0, 4.0, 2.0);
	if(sum < -0.005021484103053808 * factor)
		stage_sum += 0.18935389816761017;
	else
		stage_sum += 0.5782774090766907;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 7.0, 20.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 9.0, 20.0, 2.0, 3.0);
	if(sum < 0.0026365420781075954 * factor)
		stage_sum += 0.23093290627002716;
	else
		stage_sum += 0.5695425868034363;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 0.0, 6.0, 17.0, -1.0);
	sum += rect_sum_ii(9.0, 0.0, 2.0, 17.0, 3.0);
	if(sum < -0.0015127769438549876 * factor)
		stage_sum += 0.27596020698547363;
	else
		stage_sum += 0.5956642031669617;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 0.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 0.0, 2.0, 4.0, 3.0);
	if(sum < -0.010157439857721329 * factor)
		stage_sum += 0.17325380444526672;
	else
		stage_sum += 0.5522047281265259;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 1.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 1.0, 2.0, 4.0, 3.0);
	if(sum < -0.011953660286962986 * factor)
		stage_sum += 0.13394099473953247;
	else
		stage_sum += 0.5559014081954956;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 1.0, 6.0, 16.0, -1.0);
	sum += rect_sum_ii(14.0, 1.0, 2.0, 16.0, 3.0);
	if(sum < 0.004885949194431305 * factor)
		stage_sum += 0.36287039518356323;
	else
		stage_sum += 0.6188849210739136;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 18.0, 8.0, -1.0);
	sum += rect_sum_ii(0.0, 5.0, 9.0, 4.0, 2.0);
	sum += rect_sum_ii(9.0, 9.0, 9.0, 4.0, 2.0);
	if(sum < -0.08013291656970978 * factor)
		stage_sum += 0.09121105074882507;
	else
		stage_sum += 0.5475944876670837;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 15.0, 10.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 15.0, 5.0, 2.0, 2.0);
	sum += rect_sum_ii(8.0, 17.0, 5.0, 2.0, 2.0);
	if(sum < 0.0010643280111253262 * factor)
		stage_sum += 0.37151429057121277;
	else
		stage_sum += 0.5711399912834167;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 1.0, 4.0, 8.0, -1.0);
	sum += rect_sum_ii(3.0, 1.0, 2.0, 4.0, 2.0);
	sum += rect_sum_ii(5.0, 5.0, 2.0, 4.0, 2.0);
	if(sum < -0.0013419450260698795 * factor)
		stage_sum += 0.5953313708305359;
	else
		stage_sum += 0.33180978894233704;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 6.0, 14.0, 10.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 7.0, 5.0, 2.0);
	sum += rect_sum_ii(3.0, 11.0, 7.0, 5.0, 2.0);
	if(sum < -0.054601140320301056 * factor)
		stage_sum += 0.1844065934419632;
	else
		stage_sum += 0.5602846145629883;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 1.0, 6.0, 16.0, -1.0);
	sum += rect_sum_ii(4.0, 1.0, 2.0, 16.0, 3.0);
	if(sum < 0.0029071690514683723 * factor)
		stage_sum += 0.3594244122505188;
	else
		stage_sum += 0.6131715178489685;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 18.0, 20.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 19.0, 20.0, 1.0, 2.0);
	if(sum < 0.0007471871795132756 * factor)
		stage_sum += 0.5994353294372559;
	else
		stage_sum += 0.34595629572868347;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 13.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 14.0, 4.0, 1.0, 3.0);
	if(sum < 0.004301380831748247 * factor)
		stage_sum += 0.4172652065753937;
	else
		stage_sum += 0.6990845203399658;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 14.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 15.0, 2.0, 1.0, 3.0);
	if(sum < 0.004501757211983204 * factor)
		stage_sum += 0.4509715139865875;
	else
		stage_sum += 0.7801457047462463;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 12.0, 9.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 9.0, 2.0, 3.0);
	if(sum < 0.024138500913977623 * factor)
		stage_sum += 0.5438212752342224;
	else
		stage_sum += 0.1319826990365982;


	if(stage_sum > 9.498542785644531)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage3(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(5.0, 9.0, 3.0, 2.0, 2.0);
	if(sum < 0.001921223010867834 * factor)
		stage_sum += 0.1415266990661621;
	else
		stage_sum += 0.6199870705604553;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 3.0, 2.0, 16.0, -1.0);
	sum += rect_sum_ii(9.0, 11.0, 2.0, 8.0, 2.0);
	if(sum < -0.00012748669541906565 * factor)
		stage_sum += 0.6191074252128601;
	else
		stage_sum += 0.18849289417266846;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 6.0, 13.0, 8.0, -1.0);
	sum += rect_sum_ii(3.0, 10.0, 13.0, 4.0, 2.0);
	if(sum < 0.0005140993162058294 * factor)
		stage_sum += 0.14873969554901123;
	else
		stage_sum += 0.5857927799224854;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 3.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 3.0, 4.0, 2.0, 2.0);
	if(sum < 0.004187860991805792 * factor)
		stage_sum += 0.27469098567962646;
	else
		stage_sum += 0.6359239816665649;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 8.0, 4.0, 12.0, -1.0);
	sum += rect_sum_ii(8.0, 12.0, 4.0, 4.0, 3.0);
	if(sum < 0.005101571790874004 * factor)
		stage_sum += 0.5870851278305054;
	else
		stage_sum += 0.21756289899349213;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 3.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(15.0, 3.0, 4.0, 3.0, 2.0);
	sum += rect_sum_ii(11.0, 6.0, 4.0, 3.0, 2.0);
	if(sum < -0.002144844038411975 * factor)
		stage_sum += 0.5880944728851318;
	else
		stage_sum += 0.2979590892791748;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 1.0, 6.0, 19.0, -1.0);
	sum += rect_sum_ii(9.0, 1.0, 2.0, 19.0, 3.0);
	if(sum < -0.0028977119363844395 * factor)
		stage_sum += 0.23733270168304443;
	else
		stage_sum += 0.5876647233963013;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 0.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 0.0, 2.0, 4.0, 3.0);
	if(sum < -0.021610679104924202 * factor)
		stage_sum += 0.12206549942493439;
	else
		stage_sum += 0.5194202065467834;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 1.0, 9.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 1.0, 3.0, 3.0, 3.0);
	if(sum < -0.004629931878298521 * factor)
		stage_sum += 0.263123095035553;
	else
		stage_sum += 0.5817409157752991;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 15.0, 10.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 15.0, 5.0, 2.0, 2.0);
	sum += rect_sum_ii(8.0, 17.0, 5.0, 2.0, 2.0);
	if(sum < 0.000593937118537724 * factor)
		stage_sum += 0.363862007856369;
	else
		stage_sum += 0.5698544979095459;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 3.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(3.0, 3.0, 3.0, 10.0, 2.0);
	if(sum < 0.05387866124510765 * factor)
		stage_sum += 0.4303531050682068;
	else
		stage_sum += 0.7559366226196289;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 4.0, 15.0, 15.0, -1.0);
	sum += rect_sum_ii(3.0, 9.0, 15.0, 5.0, 3.0);
	if(sum < 0.0018887349870055914 * factor)
		stage_sum += 0.21226030588150024;
	else
		stage_sum += 0.561342716217041;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 5.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 7.0, 8.0, 2.0, 3.0);
	if(sum < -0.0023635339457541704 * factor)
		stage_sum += 0.563184916973114;
	else
		stage_sum += 0.2642767131328583;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 12.0, 10.0, -1.0);
	sum += rect_sum_ii(10.0, 4.0, 6.0, 5.0, 2.0);
	sum += rect_sum_ii(4.0, 9.0, 6.0, 5.0, 2.0);
	if(sum < 0.024017799645662308 * factor)
		stage_sum += 0.5797107815742493;
	else
		stage_sum += 0.27517059445381165;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 4.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 4.0, 2.0, 4.0, 2.0);
	if(sum < 0.00020543030404951423 * factor)
		stage_sum += 0.27052420377731323;
	else
		stage_sum += 0.575256884098053;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 11.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(15.0, 12.0, 1.0, 1.0, 2.0);
	if(sum < 0.0008479019743390381 * factor)
		stage_sum += 0.5435624718666077;
	else
		stage_sum += 0.23348769545555115;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 11.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(3.0, 12.0, 2.0, 1.0, 2.0);
	if(sum < 0.0014091329649090767 * factor)
		stage_sum += 0.5319424867630005;
	else
		stage_sum += 0.20631550252437592;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 11.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(16.0, 12.0, 1.0, 1.0, 3.0);
	if(sum < 0.0014642629539594054 * factor)
		stage_sum += 0.5418980717658997;
	else
		stage_sum += 0.30688610672950745;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 15.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(3.0, 15.0, 3.0, 2.0, 2.0);
	sum += rect_sum_ii(6.0, 17.0, 3.0, 2.0, 2.0);
	if(sum < 0.0016352549428120255 * factor)
		stage_sum += 0.3695372939109802;
	else
		stage_sum += 0.6112868189811707;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 7.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 8.0, 8.0, 1.0, 2.0);
	if(sum < 0.0008317275205627084 * factor)
		stage_sum += 0.3565036952495575;
	else
		stage_sum += 0.6025236248970032;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 11.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 12.0, 1.0, 1.0, 3.0);
	if(sum < -0.0020998890977352858 * factor)
		stage_sum += 0.19139820337295532;
	else
		stage_sum += 0.5362827181816101;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 1.0, 12.0, 1.0, 2.0);
	if(sum < -0.0007421398186124861 * factor)
		stage_sum += 0.38355550169944763;
	else
		stage_sum += 0.552931010723114;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 14.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 15.0, 2.0, 1.0, 3.0);
	if(sum < 0.0032655049581080675 * factor)
		stage_sum += 0.4312896132469177;
	else
		stage_sum += 0.7101895809173584;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 15.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 16.0, 6.0, 1.0, 2.0);
	if(sum < 0.0008913499186746776 * factor)
		stage_sum += 0.3984830975532532;
	else
		stage_sum += 0.6391963958740234;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 7.0, 4.0, 2.0, 3.0);
	if(sum < -0.015284179709851742 * factor)
		stage_sum += 0.2366732954978943;
	else
		stage_sum += 0.5433713793754578;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 12.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 12.0, 4.0, 2.0, 3.0);
	if(sum < 0.004838141147047281 * factor)
		stage_sum += 0.5817500948905945;
	else
		stage_sum += 0.3239189088344574;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 3.0, 1.0, 9.0, -1.0);
	sum += rect_sum_ii(6.0, 6.0, 1.0, 3.0, 3.0);
	if(sum < -0.0009109317907132208 * factor)
		stage_sum += 0.5540593862533569;
	else
		stage_sum += 0.2911868989467621;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 17.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 17.0, 1.0, 2.0, 3.0);
	if(sum < -0.006127506028860807 * factor)
		stage_sum += 0.17752550542354584;
	else
		stage_sum += 0.5196629166603088;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 9.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 10.0, 2.0, 1.0, 2.0);
	if(sum < -0.00044576259097084403 * factor)
		stage_sum += 0.30241701006889343;
	else
		stage_sum += 0.5533593893051147;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 2.0, 4.0, 3.0);
	if(sum < 0.02264654077589512 * factor)
		stage_sum += 0.44149309396743774;
	else
		stage_sum += 0.6975377202033997;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 17.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 17.0, 1.0, 2.0, 3.0);
	if(sum < -0.0018804960418492556 * factor)
		stage_sum += 0.2791394889354706;
	else
		stage_sum += 0.5497952103614807;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 17.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 17.0, 1.0, 3.0, 3.0);
	if(sum < 0.007088910788297653 * factor)
		stage_sum += 0.5263199210166931;
	else
		stage_sum += 0.2385547012090683;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 13.0, 3.0, 1.0, 2.0);
	if(sum < 0.0017318050377070904 * factor)
		stage_sum += 0.43193790316581726;
	else
		stage_sum += 0.6983600854873657;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 3.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 3.0, 2.0, 2.0, 3.0);
	if(sum < -0.006848270073533058 * factor)
		stage_sum += 0.3082042932510376;
	else
		stage_sum += 0.5390920042991638;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 11.0, 14.0, 4.0, -1.0);
	sum += rect_sum_ii(3.0, 13.0, 14.0, 2.0, 2.0);
	if(sum < -0.000015062530110299122 * factor)
		stage_sum += 0.552192211151123;
	else
		stage_sum += 0.3120366036891937;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 10.0, 18.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 10.0, 9.0, 2.0, 2.0);
	sum += rect_sum_ii(1.0, 12.0, 9.0, 2.0, 2.0);
	if(sum < 0.02947556972503662 * factor)
		stage_sum += 0.5401322841644287;
	else
		stage_sum += 0.1770603060722351;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 10.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 11.0, 3.0, 1.0, 3.0);
	if(sum < 0.008138732984662056 * factor)
		stage_sum += 0.5178617835044861;
	else
		stage_sum += 0.12110190093517303;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 1.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(11.0, 1.0, 2.0, 6.0, 3.0);
	if(sum < 0.02094295062124729 * factor)
		stage_sum += 0.5290294289588928;
	else
		stage_sum += 0.33112218976020813;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 1.0, 6.0, 3.0);
	if(sum < -0.009566552937030792 * factor)
		stage_sum += 0.7471994161605835;
	else
		stage_sum += 0.44519689679145813;


	if(stage_sum > 18.4129695892334)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage4(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 18.0, 9.0, -1.0);
	sum += rect_sum_ii(1.0, 3.0, 18.0, 3.0, 3.0);
	if(sum < -0.00028206960996612906 * factor)
		stage_sum += 0.20640860497951508;
	else
		stage_sum += 0.6076732277870178;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 10.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(12.0, 13.0, 2.0, 3.0, 2.0);
	if(sum < 0.00167906004935503 * factor)
		stage_sum += 0.5851997137069702;
	else
		stage_sum += 0.1255383938550949;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 19.0, 8.0, -1.0);
	sum += rect_sum_ii(0.0, 9.0, 19.0, 4.0, 2.0);
	if(sum < 0.0006982791237533092 * factor)
		stage_sum += 0.09401842951774597;
	else
		stage_sum += 0.5728961229324341;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 0.0, 6.0, 9.0, -1.0);
	sum += rect_sum_ii(9.0, 0.0, 2.0, 9.0, 3.0);
	if(sum < 0.0007895901217125356 * factor)
		stage_sum += 0.17819879949092865;
	else
		stage_sum += 0.5694308876991272;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 3.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 3.0, 2.0, 1.0, 3.0);
	if(sum < -0.002856049919500947 * factor)
		stage_sum += 0.1638399064540863;
	else
		stage_sum += 0.5788664817810059;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 3.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(13.0, 3.0, 2.0, 1.0, 3.0);
	if(sum < -0.0038122469559311867 * factor)
		stage_sum += 0.20854400098323822;
	else
		stage_sum += 0.5508564710617065;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 10.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 13.0, 4.0, 3.0, 2.0);
	if(sum < 0.0015896620461717248 * factor)
		stage_sum += 0.5702760815620422;
	else
		stage_sum += 0.1857215017080307;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 3.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(13.0, 3.0, 2.0, 1.0, 3.0);
	if(sum < 0.010078339837491512 * factor)
		stage_sum += 0.5116943120956421;
	else
		stage_sum += 0.21897700428962708;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 12.0, 6.0, -1.0);
	sum += rect_sum_ii(4.0, 6.0, 12.0, 2.0, 3.0);
	if(sum < -0.06352630257606506 * factor)
		stage_sum += 0.7131379842758179;
	else
		stage_sum += 0.40438130497932434;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 12.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(15.0, 14.0, 2.0, 2.0, 3.0);
	if(sum < -0.009103149175643921 * factor)
		stage_sum += 0.2567181885242462;
	else
		stage_sum += 0.54639732837677;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 3.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 3.0, 1.0, 2.0, 2.0);
	if(sum < -0.002403500024229288 * factor)
		stage_sum += 0.17006659507751465;
	else
		stage_sum += 0.559097409248352;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 3.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(10.0, 3.0, 1.0, 1.0, 3.0);
	if(sum < 0.001522636041045189 * factor)
		stage_sum += 0.5410556793212891;
	else
		stage_sum += 0.26190540194511414;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 1.0, 4.0, 14.0, -1.0);
	sum += rect_sum_ii(3.0, 1.0, 2.0, 14.0, 2.0);
	if(sum < 0.017997439950704575 * factor)
		stage_sum += 0.37324368953704834;
	else
		stage_sum += 0.6535220742225647;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 0.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 0.0, 2.0, 2.0, 2.0);
	sum += rect_sum_ii(9.0, 2.0, 2.0, 2.0, 2.0);
	if(sum < -0.00645381910726428 * factor)
		stage_sum += 0.26264819502830505;
	else
		stage_sum += 0.5537446141242981;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 5.0, 1.0, 14.0, -1.0);
	sum += rect_sum_ii(7.0, 12.0, 1.0, 7.0, 2.0);
	if(sum < -0.011880760081112385 * factor)
		stage_sum += 0.20037539303302765;
	else
		stage_sum += 0.5544745922088623;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 0.0, 1.0, 4.0, -1.0);
	sum += rect_sum_ii(19.0, 2.0, 1.0, 2.0, 2.0);
	if(sum < 0.0012713660253211856 * factor)
		stage_sum += 0.5591902732849121;
	else
		stage_sum += 0.30319759249687195;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 3.0, 4.0, 2.0);
	if(sum < 0.0011376109905540943 * factor)
		stage_sum += 0.2730407118797302;
	else
		stage_sum += 0.5646508932113647;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 18.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 18.0, 1.0, 2.0, 3.0);
	if(sum < -0.00426519988104701 * factor)
		stage_sum += 0.14059090614318848;
	else
		stage_sum += 0.5461820960044861;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 18.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 18.0, 1.0, 2.0, 3.0);
	if(sum < -0.0029602861031889915 * factor)
		stage_sum += 0.17950350046157837;
	else
		stage_sum += 0.5459290146827698;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 5.0, 12.0, 6.0, -1.0);
	sum += rect_sum_ii(4.0, 7.0, 12.0, 2.0, 3.0);
	if(sum < -0.008844822645187378 * factor)
		stage_sum += 0.5736783146858215;
	else
		stage_sum += 0.280921995639801;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 12.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 14.0, 2.0, 2.0, 3.0);
	if(sum < -0.006643068976700306 * factor)
		stage_sum += 0.2370675951242447;
	else
		stage_sum += 0.5503826141357422;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 8.0, 2.0, 12.0, -1.0);
	sum += rect_sum_ii(10.0, 12.0, 2.0, 4.0, 3.0);
	if(sum < 0.003999780863523483 * factor)
		stage_sum += 0.5608199834823608;
	else
		stage_sum += 0.33042821288108826;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 18.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 18.0, 1.0, 2.0, 3.0);
	if(sum < -0.004122172016650438 * factor)
		stage_sum += 0.16401059925556183;
	else
		stage_sum += 0.5378993153572083;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 0.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 0.0, 2.0, 2.0, 3.0);
	if(sum < 0.015624909661710262 * factor)
		stage_sum += 0.5227649211883545;
	else
		stage_sum += 0.22886039316654205;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 11.0, 9.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 12.0, 9.0, 1.0, 3.0);
	if(sum < -0.01035641971975565 * factor)
		stage_sum += 0.7016193866729736;
	else
		stage_sum += 0.4252927899360657;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 0.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 0.0, 2.0, 2.0, 3.0);
	if(sum < -0.008796080946922302 * factor)
		stage_sum += 0.27673470973968506;
	else
		stage_sum += 0.5355830192565918;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 1.0, 18.0, 5.0, -1.0);
	sum += rect_sum_ii(7.0, 1.0, 6.0, 5.0, 3.0);
	if(sum < 0.16226939857006073 * factor)
		stage_sum += 0.434224009513855;
	else
		stage_sum += 0.744257926940918;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 0.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 0.0, 2.0, 2.0, 2.0);
	sum += rect_sum_ii(8.0, 2.0, 2.0, 2.0, 2.0);
	if(sum < 0.0045542530715465546 * factor)
		stage_sum += 0.5726485848426819;
	else
		stage_sum += 0.25821250677108765;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 12.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 13.0, 1.0, 1.0, 3.0);
	if(sum < -0.002130920998752117 * factor)
		stage_sum += 0.21068480610847473;
	else
		stage_sum += 0.5361018776893616;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 5.0, 1.0, 3.0);
	if(sum < -0.013208420015871525 * factor)
		stage_sum += 0.7593790888786316;
	else
		stage_sum += 0.45524680614471436;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 10.0, 12.0, -1.0);
	sum += rect_sum_ii(5.0, 4.0, 5.0, 6.0, 2.0);
	sum += rect_sum_ii(10.0, 10.0, 5.0, 6.0, 2.0);
	if(sum < -0.0659966766834259 * factor)
		stage_sum += 0.12524759769439697;
	else
		stage_sum += 0.5344039797782898;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 6.0, 9.0, 12.0, -1.0);
	sum += rect_sum_ii(9.0, 10.0, 9.0, 4.0, 3.0);
	if(sum < 0.007914265617728233 * factor)
		stage_sum += 0.3315384089946747;
	else
		stage_sum += 0.5601043105125427;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 2.0, 12.0, 14.0, -1.0);
	sum += rect_sum_ii(2.0, 2.0, 6.0, 7.0, 2.0);
	sum += rect_sum_ii(8.0, 9.0, 6.0, 7.0, 2.0);
	if(sum < 0.020894279703497887 * factor)
		stage_sum += 0.5506049990653992;
	else
		stage_sum += 0.2768838107585907;


	if(stage_sum > 15.324139595031738)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage5(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 7.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 4.0, 2.0, 3.0);
	if(sum < 0.0011961159761995077 * factor)
		stage_sum += 0.17626909911632538;
	else
		stage_sum += 0.6156241297721863;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 4.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 6.0, 6.0, 2.0, 2.0);
	if(sum < -0.0018679830245673656 * factor)
		stage_sum += 0.6118106842041016;
	else
		stage_sum += 0.18323999643325806;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 5.0, 11.0, 8.0, -1.0);
	sum += rect_sum_ii(4.0, 9.0, 11.0, 4.0, 2.0);
	if(sum < -0.00019579799845814705 * factor)
		stage_sum += 0.09904426336288452;
	else
		stage_sum += 0.5723816156387329;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 10.0, 16.0, 4.0, -1.0);
	sum += rect_sum_ii(3.0, 12.0, 16.0, 2.0, 2.0);
	if(sum < -0.0008025565766729414 * factor)
		stage_sum += 0.5579879879951477;
	else
		stage_sum += 0.2377282977104187;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 16.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 1.0, 16.0, 1.0, 2.0);
	if(sum < -0.0024510810617357492 * factor)
		stage_sum += 0.22314579784870148;
	else
		stage_sum += 0.5858935117721558;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 5.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 2.0, 2.0, 3.0);
	if(sum < 0.0005036185029894114 * factor)
		stage_sum += 0.26539939641952515;
	else
		stage_sum += 0.5794103741645813;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 2.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(3.0, 2.0, 3.0, 5.0, 2.0);
	sum += rect_sum_ii(6.0, 7.0, 3.0, 5.0, 2.0);
	if(sum < 0.0040293349884450436 * factor)
		stage_sum += 0.5803827047348022;
	else
		stage_sum += 0.2484865039587021;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 5.0, 8.0, 15.0, -1.0);
	sum += rect_sum_ii(10.0, 10.0, 8.0, 5.0, 3.0);
	if(sum < -0.0144517095759511 * factor)
		stage_sum += 0.18303519487380981;
	else
		stage_sum += 0.5484204888343811;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 14.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 14.0, 4.0, 3.0, 2.0);
	sum += rect_sum_ii(7.0, 17.0, 4.0, 3.0, 2.0);
	if(sum < 0.0020380979403853416 * factor)
		stage_sum += 0.33635589480400085;
	else
		stage_sum += 0.6051092743873596;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 2.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(14.0, 3.0, 2.0, 1.0, 2.0);
	if(sum < -0.0016155190533027053 * factor)
		stage_sum += 0.22866420447826385;
	else
		stage_sum += 0.5441246032714844;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 10.0, 7.0, 6.0, -1.0);
	sum += rect_sum_ii(1.0, 13.0, 7.0, 3.0, 2.0);
	if(sum < 0.0033458340913057327 * factor)
		stage_sum += 0.5625913143157959;
	else
		stage_sum += 0.2392338067293167;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 4.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 4.0, 2.0, 3.0, 2.0);
	if(sum < 0.0016379579901695251 * factor)
		stage_sum += 0.3906993865966797;
	else
		stage_sum += 0.5964621901512146;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 9.0, 14.0, 6.0, -1.0);
	sum += rect_sum_ii(2.0, 9.0, 7.0, 3.0, 2.0);
	sum += rect_sum_ii(9.0, 12.0, 7.0, 3.0, 2.0);
	if(sum < 0.030251210555434227 * factor)
		stage_sum += 0.524848222732544;
	else
		stage_sum += 0.15757469832897186;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 10.0, 4.0, -1.0);
	sum += rect_sum_ii(5.0, 9.0, 10.0, 2.0, 2.0);
	if(sum < 0.03725199028849602 * factor)
		stage_sum += 0.41943109035491943;
	else
		stage_sum += 0.6748418807983398;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 9.0, 8.0, 8.0, -1.0);
	sum += rect_sum_ii(6.0, 9.0, 4.0, 4.0, 2.0);
	sum += rect_sum_ii(10.0, 13.0, 4.0, 4.0, 2.0);
	if(sum < -0.02510979026556015 * factor)
		stage_sum += 0.18825499713420868;
	else
		stage_sum += 0.5473451018333435;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 1.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(14.0, 2.0, 3.0, 1.0, 2.0);
	if(sum < -0.005309905856847763 * factor)
		stage_sum += 0.13399730622768402;
	else
		stage_sum += 0.5227110981941223;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 4.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(3.0, 4.0, 2.0, 2.0, 2.0);
	if(sum < 0.0012086479691788554 * factor)
		stage_sum += 0.3762088119983673;
	else
		stage_sum += 0.6109635829925537;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 10.0, 2.0, 8.0, -1.0);
	sum += rect_sum_ii(11.0, 14.0, 2.0, 4.0, 2.0);
	if(sum < -0.021907679736614227 * factor)
		stage_sum += 0.266314297914505;
	else
		stage_sum += 0.5404006838798523;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 1.0, 5.0, 1.0, 3.0);
	if(sum < 0.0054116579703986645 * factor)
		stage_sum += 0.5363578796386719;
	else
		stage_sum += 0.22322730720043182;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 5.0, 18.0, 8.0, -1.0);
	sum += rect_sum_ii(11.0, 5.0, 9.0, 4.0, 2.0);
	sum += rect_sum_ii(2.0, 9.0, 9.0, 4.0, 2.0);
	if(sum < 0.06994632631540298 * factor)
		stage_sum += 0.5358232855796814;
	else
		stage_sum += 0.2453698068857193;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 1.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 9.0, 1.0, 3.0, 2.0);
	if(sum < 0.00034520021290518343 * factor)
		stage_sum += 0.24096719920635223;
	else
		stage_sum += 0.5376930236816406;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 1.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(19.0, 2.0, 1.0, 1.0, 3.0);
	if(sum < 0.0012627709656953812 * factor)
		stage_sum += 0.5425856709480286;
	else
		stage_sum += 0.31556931138038635;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 2.0, 6.0, 3.0);
	if(sum < 0.02271950989961624 * factor)
		stage_sum += 0.41584059596061707;
	else
		stage_sum += 0.6597865223884583;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 1.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(19.0, 2.0, 1.0, 1.0, 3.0);
	if(sum < -0.001811100053600967 * factor)
		stage_sum += 0.2811253070831299;
	else
		stage_sum += 0.5505244731903076;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 13.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 14.0, 2.0, 1.0, 3.0);
	if(sum < 0.0033469670452177525 * factor)
		stage_sum += 0.526002824306488;
	else
		stage_sum += 0.1891465038061142;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 4.0, 8.0, 12.0, -1.0);
	sum += rect_sum_ii(12.0, 4.0, 4.0, 6.0, 2.0);
	sum += rect_sum_ii(8.0, 10.0, 4.0, 6.0, 2.0);
	if(sum < 0.00040791751234792173 * factor)
		stage_sum += 0.5673509240150452;
	else
		stage_sum += 0.3344210088253021;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 2.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 2.0, 2.0, 3.0, 3.0);
	if(sum < 0.012734799645841122 * factor)
		stage_sum += 0.5343592166900635;
	else
		stage_sum += 0.23956120014190674;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 1.0, 9.0, 10.0, -1.0);
	sum += rect_sum_ii(6.0, 6.0, 9.0, 5.0, 2.0);
	if(sum < -0.007311972789466381 * factor)
		stage_sum += 0.6010890007019043;
	else
		stage_sum += 0.40222078561782837;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 4.0, 6.0, 12.0, -1.0);
	sum += rect_sum_ii(2.0, 4.0, 2.0, 12.0, 3.0);
	if(sum < -0.05694875121116638 * factor)
		stage_sum += 0.8199151158332825;
	else
		stage_sum += 0.4543190896511078;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 13.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 14.0, 2.0, 1.0, 3.0);
	if(sum < -0.005011659115552902 * factor)
		stage_sum += 0.2200281023979187;
	else
		stage_sum += 0.5357710719108582;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 14.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 15.0, 5.0, 1.0, 3.0);
	if(sum < 0.006033436860889196 * factor)
		stage_sum += 0.4413081109523773;
	else
		stage_sum += 0.7181751132011414;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 13.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 14.0, 3.0, 1.0, 3.0);
	if(sum < 0.0039437441155314445 * factor)
		stage_sum += 0.547886073589325;
	else
		stage_sum += 0.2791733145713806;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 14.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 15.0, 8.0, 1.0, 3.0);
	if(sum < -0.0036591119132936 * factor)
		stage_sum += 0.635786771774292;
	else
		stage_sum += 0.39897239208221436;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 13.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 14.0, 3.0, 1.0, 3.0);
	if(sum < -0.0038456181064248085 * factor)
		stage_sum += 0.3493686020374298;
	else
		stage_sum += 0.5300664901733398;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 13.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(2.0, 14.0, 3.0, 1.0, 3.0);
	if(sum < -0.007192626129835844 * factor)
		stage_sum += 0.1119614988565445;
	else
		stage_sum += 0.5229672789573669;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 7.0, 12.0, 12.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 6.0, 6.0, 2.0);
	sum += rect_sum_ii(4.0, 13.0, 6.0, 6.0, 2.0);
	if(sum < -0.05279894173145294 * factor)
		stage_sum += 0.23871029913425446;
	else
		stage_sum += 0.54534512758255;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 6.0, 2.0);
	if(sum < -0.007953766733407974 * factor)
		stage_sum += 0.7586917877197266;
	else
		stage_sum += 0.4439376890659332;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 9.0, 5.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 10.0, 5.0, 1.0, 2.0);
	if(sum < -0.0027344180271029472 * factor)
		stage_sum += 0.2565476894378662;
	else
		stage_sum += 0.5489321947097778;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 6.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 1.0, 4.0, 3.0);
	if(sum < -0.0018507939530536532 * factor)
		stage_sum += 0.6734347939491272;
	else
		stage_sum += 0.4252474904060364;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 6.0, 2.0, 8.0, -1.0);
	sum += rect_sum_ii(9.0, 10.0, 2.0, 4.0, 2.0);
	if(sum < 0.015918919816613197 * factor)
		stage_sum += 0.548835277557373;
	else
		stage_sum += 0.2292661964893341;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 1.0, 6.0, 3.0);
	if(sum < -0.0012687679845839739 * factor)
		stage_sum += 0.6104331016540527;
	else
		stage_sum += 0.40223899483680725;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 3.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 3.0, 1.0, 3.0, 3.0);
	if(sum < 0.006288391072303057 * factor)
		stage_sum += 0.5310853123664856;
	else
		stage_sum += 0.15361930429935455;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 4.0, 2.0, 1.0, 3.0);
	if(sum < -0.0062259892001748085 * factor)
		stage_sum += 0.17291119694709778;
	else
		stage_sum += 0.524160623550415;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 10.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 7.0, 10.0, 1.0, 3.0);
	if(sum < -0.012132599949836731 * factor)
		stage_sum += 0.659775972366333;
	else
		stage_sum += 0.43251821398735046;


	if(stage_sum > 21.010639190673828)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage6(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 3.0, 6.0, 9.0, -1.0);
	sum += rect_sum_ii(7.0, 6.0, 6.0, 3.0, 3.0);
	if(sum < -0.0039184908382594585 * factor)
		stage_sum += 0.6103435158729553;
	else
		stage_sum += 0.14693309366703033;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 7.0, 9.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 3.0, 1.0, 3.0);
	if(sum < 0.0015971299726516008 * factor)
		stage_sum += 0.26323631405830383;
	else
		stage_sum += 0.5896466970443726;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 8.0, 16.0, 8.0, -1.0);
	sum += rect_sum_ii(2.0, 12.0, 16.0, 4.0, 2.0);
	if(sum < 0.017780110239982605 * factor)
		stage_sum += 0.587287425994873;
	else
		stage_sum += 0.17603619396686554;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 6.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(14.0, 9.0, 2.0, 3.0, 2.0);
	if(sum < 0.0006533476989716291 * factor)
		stage_sum += 0.1567801982164383;
	else
		stage_sum += 0.5596066117286682;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 5.0, 6.0, 15.0, -1.0);
	sum += rect_sum_ii(1.0, 10.0, 6.0, 5.0, 3.0);
	if(sum < -0.00028353091329336166 * factor)
		stage_sum += 0.1913153976202011;
	else
		stage_sum += 0.5732036232948303;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 0.0, 6.0, 9.0, -1.0);
	sum += rect_sum_ii(10.0, 3.0, 6.0, 3.0, 3.0);
	if(sum < 0.0016104689566418529 * factor)
		stage_sum += 0.29149138927459717;
	else
		stage_sum += 0.5623080730438232;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 7.0, 14.0, -1.0);
	sum += rect_sum_ii(6.0, 13.0, 7.0, 7.0, 2.0);
	if(sum < -0.09775061905384064 * factor)
		stage_sum += 0.19434769451618195;
	else
		stage_sum += 0.5648233294487;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(13.0, 9.0, 3.0, 2.0, 3.0);
	if(sum < 0.0005518235848285258 * factor)
		stage_sum += 0.31346169114112854;
	else
		stage_sum += 0.5504639744758606;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 8.0, 15.0, 4.0, -1.0);
	sum += rect_sum_ii(6.0, 8.0, 5.0, 4.0, 3.0);
	if(sum < -0.012858220376074314 * factor)
		stage_sum += 0.25364819169044495;
	else
		stage_sum += 0.5760142803192139;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 2.0, 3.0, 10.0, -1.0);
	sum += rect_sum_ii(11.0, 7.0, 3.0, 5.0, 2.0);
	if(sum < 0.004153023939579725 * factor)
		stage_sum += 0.5767722129821777;
	else
		stage_sum += 0.36597740650177;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 7.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 9.0, 4.0, 2.0, 3.0);
	if(sum < 0.0017092459602281451 * factor)
		stage_sum += 0.28431910276412964;
	else
		stage_sum += 0.5918939113616943;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 3.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(15.0, 3.0, 2.0, 10.0, 3.0);
	if(sum < 0.007521735969930887 * factor)
		stage_sum += 0.4052427113056183;
	else
		stage_sum += 0.6183109283447266;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 8.0, 10.0, -1.0);
	sum += rect_sum_ii(5.0, 7.0, 4.0, 5.0, 2.0);
	sum += rect_sum_ii(9.0, 12.0, 4.0, 5.0, 2.0);
	if(sum < 0.0022479810286313295 * factor)
		stage_sum += 0.578375518321991;
	else
		stage_sum += 0.31354010105133057;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 12.0, 12.0, -1.0);
	sum += rect_sum_ii(10.0, 4.0, 6.0, 6.0, 2.0);
	sum += rect_sum_ii(4.0, 10.0, 6.0, 6.0, 2.0);
	if(sum < 0.05200621113181114 * factor)
		stage_sum += 0.5541312098503113;
	else
		stage_sum += 0.1916636973619461;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 4.0, 6.0, 9.0, -1.0);
	sum += rect_sum_ii(3.0, 4.0, 2.0, 9.0, 3.0);
	if(sum < 0.01208552997559309 * factor)
		stage_sum += 0.4032655954360962;
	else
		stage_sum += 0.6644591093063354;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 3.0, 2.0, 5.0, -1.0);
	sum += rect_sum_ii(11.0, 3.0, 1.0, 5.0, 2.0);
	if(sum < 0.000014687820112158079 * factor)
		stage_sum += 0.3535977900028229;
	else
		stage_sum += 0.5709382891654968;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 3.0, 2.0, 5.0, -1.0);
	sum += rect_sum_ii(8.0, 3.0, 1.0, 5.0, 2.0);
	if(sum < 0.000007139518857002258 * factor)
		stage_sum += 0.30374449491500854;
	else
		stage_sum += 0.5610269904136658;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 14.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 15.0, 2.0, 1.0, 3.0);
	if(sum < -0.0046001640148460865 * factor)
		stage_sum += 0.7181087136268616;
	else
		stage_sum += 0.45803260803222656;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 12.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 12.0, 3.0, 2.0, 2.0);
	if(sum < 0.0020058949012309313 * factor)
		stage_sum += 0.5621951818466187;
	else
		stage_sum += 0.29536840319633484;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 14.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 15.0, 2.0, 1.0, 3.0);
	if(sum < 0.004505027085542679 * factor)
		stage_sum += 0.46153879165649414;
	else
		stage_sum += 0.7619017958641052;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 11.0, 12.0, 6.0, -1.0);
	sum += rect_sum_ii(4.0, 14.0, 12.0, 3.0, 2.0);
	if(sum < 0.011746830306947231 * factor)
		stage_sum += 0.5343837141990662;
	else
		stage_sum += 0.1772529035806656;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 11.0, 5.0, 9.0, -1.0);
	sum += rect_sum_ii(11.0, 14.0, 5.0, 3.0, 3.0);
	if(sum < -0.05831633880734444 * factor)
		stage_sum += 0.16862459480762482;
	else
		stage_sum += 0.5340772271156311;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 15.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 16.0, 3.0, 1.0, 2.0);
	if(sum < 0.00023629379575140774 * factor)
		stage_sum += 0.3792056143283844;
	else
		stage_sum += 0.6026803851127625;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 0.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(12.0, 0.0, 1.0, 5.0, 3.0);
	if(sum < -0.007815618067979813 * factor)
		stage_sum += 0.15128670632839203;
	else
		stage_sum += 0.5324323773384094;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 6.0, 7.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 3.0, 7.0, 2.0);
	if(sum < -0.010876160115003586 * factor)
		stage_sum += 0.2081822007894516;
	else
		stage_sum += 0.5319945216178894;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 0.0, 1.0, 9.0, -1.0);
	sum += rect_sum_ii(13.0, 3.0, 1.0, 3.0, 3.0);
	if(sum < -0.0027745519764721394 * factor)
		stage_sum += 0.4098246991634369;
	else
		stage_sum += 0.5210328102111816;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 2.0, 4.0, 8.0, -1.0);
	sum += rect_sum_ii(3.0, 2.0, 2.0, 4.0, 2.0);
	sum += rect_sum_ii(5.0, 6.0, 2.0, 4.0, 2.0);
	if(sum < -0.0007827638182789087 * factor)
		stage_sum += 0.5693274140357971;
	else
		stage_sum += 0.3478842079639435;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 12.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(13.0, 14.0, 4.0, 2.0, 3.0);
	if(sum < 0.013870409689843655 * factor)
		stage_sum += 0.5326750874519348;
	else
		stage_sum += 0.2257698029279709;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 12.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 14.0, 4.0, 2.0, 3.0);
	if(sum < -0.02367491088807583 * factor)
		stage_sum += 0.1551305055618286;
	else
		stage_sum += 0.5200707912445068;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 11.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 13.0, 3.0, 2.0, 2.0);
	if(sum < -0.000014879409718560055 * factor)
		stage_sum += 0.5500566959381104;
	else
		stage_sum += 0.3820176124572754;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 5.0, 4.0, 1.0, 3.0);
	if(sum < 0.00361906411126256 * factor)
		stage_sum += 0.4238683879375458;
	else
		stage_sum += 0.6639748215675354;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 5.0, 11.0, 8.0, -1.0);
	sum += rect_sum_ii(7.0, 9.0, 11.0, 4.0, 2.0);
	if(sum < -0.019817110151052475 * factor)
		stage_sum += 0.21500380337238312;
	else
		stage_sum += 0.5382357835769653;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 8.0, 1.0, 4.0, 3.0);
	if(sum < -0.0038154039066284895 * factor)
		stage_sum += 0.6675711274147034;
	else
		stage_sum += 0.42152971029281616;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 1.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(11.0, 1.0, 2.0, 1.0, 3.0);
	if(sum < -0.0049775829538702965 * factor)
		stage_sum += 0.2267289012670517;
	else
		stage_sum += 0.5386328101158142;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 3.0, 1.0, 3.0);
	if(sum < 0.002244102070108056 * factor)
		stage_sum += 0.43086910247802734;
	else
		stage_sum += 0.6855735778808594;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 9.0, 20.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 9.0, 10.0, 3.0, 2.0);
	sum += rect_sum_ii(0.0, 12.0, 10.0, 3.0, 2.0);
	if(sum < 0.012282459996640682 * factor)
		stage_sum += 0.5836614966392517;
	else
		stage_sum += 0.34674790501594543;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 6.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 1.0, 5.0, 3.0);
	if(sum < -0.002854869933798909 * factor)
		stage_sum += 0.7016944885253906;
	else
		stage_sum += 0.43114539980888367;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 0.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 1.0, 1.0, 1.0, 3.0);
	if(sum < -0.0037875669077038765 * factor)
		stage_sum += 0.2895345091819763;
	else
		stage_sum += 0.5224946141242981;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 2.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(4.0, 3.0, 4.0, 1.0, 2.0);
	if(sum < -0.0012201230274513364 * factor)
		stage_sum += 0.2975570857524872;
	else
		stage_sum += 0.5481644868850708;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 6.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 7.0, 4.0, 1.0, 3.0);
	if(sum < 0.010160599835216999 * factor)
		stage_sum += 0.48888179659843445;
	else
		stage_sum += 0.8182697892189026;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 0.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 0.0, 2.0, 4.0, 3.0);
	if(sum < -0.016174569725990295 * factor)
		stage_sum += 0.1481492966413498;
	else
		stage_sum += 0.5239992737770081;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 8.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 8.0, 3.0);
	if(sum < 0.01929246075451374 * factor)
		stage_sum += 0.47863098978996277;
	else
		stage_sum += 0.7378190755844116;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 2.0, 2.0);
	if(sum < -0.003247953951358795 * factor)
		stage_sum += 0.7374222874641418;
	else
		stage_sum += 0.4470643997192383;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 7.0, 14.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 7.0, 7.0, 2.0, 2.0);
	sum += rect_sum_ii(6.0, 9.0, 7.0, 2.0, 2.0);
	if(sum < -0.009380348026752472 * factor)
		stage_sum += 0.3489154875278473;
	else
		stage_sum += 0.5537996292114258;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 7.0, 3.0, 2.0, 3.0);
	if(sum < -0.012606129981577396 * factor)
		stage_sum += 0.23796869814395905;
	else
		stage_sum += 0.5315443277359009;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 11.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 13.0, 3.0, 2.0, 2.0);
	if(sum < -0.02562193013727665 * factor)
		stage_sum += 0.1964688003063202;
	else
		stage_sum += 0.5138769745826721;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 11.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(4.0, 13.0, 3.0, 2.0, 2.0);
	if(sum < -0.00007574149640277028 * factor)
		stage_sum += 0.5590522885322571;
	else
		stage_sum += 0.33658531308174133;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 9.0, 12.0, 8.0, -1.0);
	sum += rect_sum_ii(11.0, 9.0, 6.0, 4.0, 2.0);
	sum += rect_sum_ii(5.0, 13.0, 6.0, 4.0, 2.0);
	if(sum < -0.0892108827829361 * factor)
		stage_sum += 0.06340465694665909;
	else
		stage_sum += 0.516263484954834;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 12.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 13.0, 1.0, 1.0, 3.0);
	if(sum < -0.002767048077657819 * factor)
		stage_sum += 0.732346773147583;
	else
		stage_sum += 0.44907060265541077;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 15.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 17.0, 2.0, 2.0, 2.0);
	if(sum < 0.0002715257869567722 * factor)
		stage_sum += 0.411483496427536;
	else
		stage_sum += 0.5985518097877502;


	if(stage_sum > 23.918790817260742)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage7(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 7.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 2.0, 1.0, 3.0);
	if(sum < 0.001478621968999505 * factor)
		stage_sum += 0.266354501247406;
	else
		stage_sum += 0.6643316745758057;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 3.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(15.0, 3.0, 3.0, 3.0, 2.0);
	sum += rect_sum_ii(12.0, 6.0, 3.0, 3.0, 2.0);
	if(sum < -0.001874165958724916 * factor)
		stage_sum += 0.6143848896026611;
	else
		stage_sum += 0.25185129046440125;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 4.0, 10.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 6.0, 10.0, 2.0, 3.0);
	if(sum < -0.001715100952424109 * factor)
		stage_sum += 0.5766341090202332;
	else
		stage_sum += 0.2397463023662567;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 3.0, 8.0, 14.0, -1.0);
	sum += rect_sum_ii(12.0, 3.0, 4.0, 7.0, 2.0);
	sum += rect_sum_ii(8.0, 10.0, 4.0, 7.0, 2.0);
	if(sum < -0.0018939269939437509 * factor)
		stage_sum += 0.5682045817375183;
	else
		stage_sum += 0.2529144883155823;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 7.0, 15.0, -1.0);
	sum += rect_sum_ii(4.0, 9.0, 7.0, 5.0, 3.0);
	if(sum < -0.005300605203956366 * factor)
		stage_sum += 0.1640675961971283;
	else
		stage_sum += 0.5556079745292664;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 2.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(15.0, 2.0, 3.0, 4.0, 2.0);
	sum += rect_sum_ii(12.0, 6.0, 3.0, 4.0, 2.0);
	if(sum < -0.04666253179311752 * factor)
		stage_sum += 0.6123154163360596;
	else
		stage_sum += 0.4762830138206482;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 2.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(2.0, 2.0, 3.0, 4.0, 2.0);
	sum += rect_sum_ii(5.0, 6.0, 3.0, 4.0, 2.0);
	if(sum < -0.000794313324149698 * factor)
		stage_sum += 0.5707858800888062;
	else
		stage_sum += 0.2839404046535492;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 13.0, 18.0, 7.0, -1.0);
	sum += rect_sum_ii(8.0, 13.0, 6.0, 7.0, 3.0);
	if(sum < 0.01489167008548975 * factor)
		stage_sum += 0.4089672863483429;
	else
		stage_sum += 0.6006367206573486;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 3.0, 8.0, 14.0, -1.0);
	sum += rect_sum_ii(4.0, 3.0, 4.0, 7.0, 2.0);
	sum += rect_sum_ii(8.0, 10.0, 4.0, 7.0, 2.0);
	if(sum < -0.0012046529445797205 * factor)
		stage_sum += 0.5712450742721558;
	else
		stage_sum += 0.2705289125442505;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 1.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(18.0, 3.0, 2.0, 2.0, 3.0);
	if(sum < 0.006061938125640154 * factor)
		stage_sum += 0.526250422000885;
	else
		stage_sum += 0.32622259855270386;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 11.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 12.0, 2.0, 1.0, 3.0);
	if(sum < -0.0025286648888140917 * factor)
		stage_sum += 0.6853830814361572;
	else
		stage_sum += 0.4199256896972656;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 1.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(18.0, 3.0, 2.0, 2.0, 3.0);
	if(sum < -0.005901021882891655 * factor)
		stage_sum += 0.3266282081604004;
	else
		stage_sum += 0.5434812903404236;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 1.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 3.0, 2.0, 2.0, 3.0);
	if(sum < 0.005670276004821062 * factor)
		stage_sum += 0.5468410849571228;
	else
		stage_sum += 0.2319003939628601;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 5.0, 18.0, 6.0, -1.0);
	sum += rect_sum_ii(1.0, 7.0, 18.0, 2.0, 3.0);
	if(sum < -0.003030410036444664 * factor)
		stage_sum += 0.557066798210144;
	else
		stage_sum += 0.27082380652427673;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 6.0, 7.0, -1.0);
	sum += rect_sum_ii(3.0, 2.0, 3.0, 7.0, 2.0);
	if(sum < 0.002980364952236414 * factor)
		stage_sum += 0.3700568974018097;
	else
		stage_sum += 0.5890625715255737;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 3.0, 6.0, 14.0, -1.0);
	sum += rect_sum_ii(7.0, 10.0, 6.0, 7.0, 2.0);
	if(sum < -0.07584051042795181 * factor)
		stage_sum += 0.21400700509548187;
	else
		stage_sum += 0.5419948101043701;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 7.0, 13.0, 10.0, -1.0);
	sum += rect_sum_ii(3.0, 12.0, 13.0, 5.0, 2.0);
	if(sum < 0.019262539222836494 * factor)
		stage_sum += 0.5526772141456604;
	else
		stage_sum += 0.2726590037345886;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 15.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 16.0, 2.0, 1.0, 2.0);
	if(sum < 0.00018888259364757687 * factor)
		stage_sum += 0.3958011865615845;
	else
		stage_sum += 0.6017209887504578;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 11.0, 16.0, 4.0, -1.0);
	sum += rect_sum_ii(2.0, 11.0, 8.0, 2.0, 2.0);
	sum += rect_sum_ii(10.0, 13.0, 8.0, 2.0, 2.0);
	if(sum < 0.029369549825787544 * factor)
		stage_sum += 0.5241373777389526;
	else
		stage_sum += 0.14357580244541168;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 7.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(16.0, 7.0, 3.0, 2.0, 2.0);
	sum += rect_sum_ii(13.0, 9.0, 3.0, 2.0, 2.0);
	if(sum < 0.0010417619487270713 * factor)
		stage_sum += 0.3385409116744995;
	else
		stage_sum += 0.5929983258247375;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 10.0, 3.0, 9.0, -1.0);
	sum += rect_sum_ii(6.0, 13.0, 3.0, 3.0, 3.0);
	if(sum < 0.0026125640142709017 * factor)
		stage_sum += 0.5485377907752991;
	else
		stage_sum += 0.30215978622436523;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 6.0, 1.0, 6.0, -1.0);
	sum += rect_sum_ii(14.0, 9.0, 1.0, 3.0, 2.0);
	if(sum < 0.0009697746718302369 * factor)
		stage_sum += 0.3375276029109955;
	else
		stage_sum += 0.553203284740448;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 10.0, 4.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 10.0, 2.0, 1.0, 2.0);
	if(sum < 0.0005951265920884907 * factor)
		stage_sum += 0.563174307346344;
	else
		stage_sum += 0.3359399139881134;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 8.0, 15.0, 5.0, -1.0);
	sum += rect_sum_ii(8.0, 8.0, 5.0, 5.0, 3.0);
	if(sum < -0.10156559944152832 * factor)
		stage_sum += 0.06373503804206848;
	else
		stage_sum += 0.5230425000190735;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 6.0, 5.0, 4.0, -1.0);
	sum += rect_sum_ii(1.0, 8.0, 5.0, 2.0, 2.0);
	if(sum < 0.03615669906139374 * factor)
		stage_sum += 0.5136963129043579;
	else
		stage_sum += 0.10295289754867554;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 1.0, 17.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 3.0, 17.0, 2.0, 3.0);
	if(sum < 0.003462414024397731 * factor)
		stage_sum += 0.3879320025444031;
	else
		stage_sum += 0.5558289289474487;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 7.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 4.0, 2.0, 2.0);
	if(sum < 0.019554980099201202 * factor)
		stage_sum += 0.5250086784362793;
	else
		stage_sum += 0.1875859946012497;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 2.0, 3.0);
	if(sum < -0.0023121440317481756 * factor)
		stage_sum += 0.667202889919281;
	else
		stage_sum += 0.4679641127586365;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 7.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 1.0, 2.0, 3.0);
	if(sum < -0.001860528951510787 * factor)
		stage_sum += 0.7163379192352295;
	else
		stage_sum += 0.4334670901298523;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 9.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 10.0, 4.0, 1.0, 2.0);
	if(sum < -0.0009402636205777526 * factor)
		stage_sum += 0.302136093378067;
	else
		stage_sum += 0.5650203227996826;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 8.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 9.0, 4.0, 1.0, 3.0);
	if(sum < -0.005241833161562681 * factor)
		stage_sum += 0.18200090527534485;
	else
		stage_sum += 0.5250256061553955;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 3.0, 4.0, 2.0);
	if(sum < 0.00011729019752237946 * factor)
		stage_sum += 0.3389188051223755;
	else
		stage_sum += 0.544597327709198;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 13.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 14.0, 4.0, 1.0, 3.0);
	if(sum < 0.0011878840159624815 * factor)
		stage_sum += 0.4085349142551422;
	else
		stage_sum += 0.6253563165664673;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 7.0, 12.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 6.0, 3.0, 2.0);
	sum += rect_sum_ii(4.0, 10.0, 6.0, 3.0, 2.0);
	if(sum < -0.010881359688937664 * factor)
		stage_sum += 0.33783990144729614;
	else
		stage_sum += 0.5700082778930664;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 4.0, 1.0, 3.0);
	if(sum < 0.0017354859737679362 * factor)
		stage_sum += 0.42046359181404114;
	else
		stage_sum += 0.6523038744926453;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 8.0, 3.0, 1.0, 3.0);
	if(sum < -0.00651190523058176 * factor)
		stage_sum += 0.25952160358428955;
	else
		stage_sum += 0.5428143739700317;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 4.0, 3.0, 8.0, -1.0);
	sum += rect_sum_ii(8.0, 4.0, 1.0, 8.0, 3.0);
	if(sum < -0.0012136430013924837 * factor)
		stage_sum += 0.6165143847465515;
	else
		stage_sum += 0.3977893888950348;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 0.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(11.0, 0.0, 1.0, 6.0, 3.0);
	if(sum < -0.01035424042493105 * factor)
		stage_sum += 0.1628028005361557;
	else
		stage_sum += 0.5219504833221436;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 3.0, 4.0, 8.0, -1.0);
	sum += rect_sum_ii(8.0, 3.0, 2.0, 8.0, 2.0);
	if(sum < 0.0005585883045569062 * factor)
		stage_sum += 0.31996509432792664;
	else
		stage_sum += 0.5503574013710022;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 3.0, 6.0, 13.0, -1.0);
	sum += rect_sum_ii(14.0, 3.0, 3.0, 13.0, 2.0);
	if(sum < 0.01529964990913868 * factor)
		stage_sum += 0.4103994071483612;
	else
		stage_sum += 0.6122388243675232;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 13.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 16.0, 3.0, 3.0, 2.0);
	if(sum < -0.02158821001648903 * factor)
		stage_sum += 0.10349129885435104;
	else
		stage_sum += 0.519738495349884;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 3.0, 6.0, 13.0, -1.0);
	sum += rect_sum_ii(14.0, 3.0, 3.0, 13.0, 2.0);
	if(sum < -0.1283462941646576 * factor)
		stage_sum += 0.8493865132331848;
	else
		stage_sum += 0.48931029438972473;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 7.0, 10.0, 4.0, -1.0);
	sum += rect_sum_ii(0.0, 7.0, 5.0, 2.0, 2.0);
	sum += rect_sum_ii(5.0, 9.0, 5.0, 2.0, 2.0);
	if(sum < -0.0022927189711481333 * factor)
		stage_sum += 0.31301578879356384;
	else
		stage_sum += 0.5471575260162354;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 3.0, 6.0, 13.0, -1.0);
	sum += rect_sum_ii(14.0, 3.0, 3.0, 13.0, 2.0);
	if(sum < 0.0799151062965393 * factor)
		stage_sum += 0.4856320917606354;
	else
		stage_sum += 0.6073989272117615;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 3.0, 6.0, 13.0, -1.0);
	sum += rect_sum_ii(3.0, 3.0, 3.0, 13.0, 2.0);
	if(sum < -0.07944109290838242 * factor)
		stage_sum += 0.8394674062728882;
	else
		stage_sum += 0.46245330572128296;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 1.0, 4.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 1.0, 2.0, 1.0, 2.0);
	if(sum < -0.00528000108897686 * factor)
		stage_sum += 0.18816959857940674;
	else
		stage_sum += 0.5306698083877563;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 0.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 0.0, 1.0, 1.0, 2.0);
	if(sum < 0.0010463109938427806 * factor)
		stage_sum += 0.5271229147911072;
	else
		stage_sum += 0.2583065927028656;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 16.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 16.0, 2.0, 2.0, 2.0);
	sum += rect_sum_ii(10.0, 18.0, 2.0, 2.0, 2.0);
	if(sum < 0.00026317298761568964 * factor)
		stage_sum += 0.4235304892063141;
	else
		stage_sum += 0.5735440850257874;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 6.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 1.0, 3.0, 2.0);
	if(sum < -0.0036173160187900066 * factor)
		stage_sum += 0.6934396028518677;
	else
		stage_sum += 0.4495444893836975;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 5.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 4.0, 2.0, 3.0);
	if(sum < 0.01142187975347042 * factor)
		stage_sum += 0.590092122554779;
	else
		stage_sum += 0.4138193130493164;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 7.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 1.0, 5.0, 3.0);
	if(sum < -0.0019963278900831938 * factor)
		stage_sum += 0.6466382741928101;
	else
		stage_sum += 0.4327239990234375;


	if(stage_sum > 24.52787971496582)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage8(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 4.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 6.0, 8.0, 2.0, 3.0);
	if(sum < -0.00996912457048893 * factor)
		stage_sum += 0.6142324209213257;
	else
		stage_sum += 0.24822120368480682;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 2.0, 12.0, -1.0);
	sum += rect_sum_ii(9.0, 11.0, 2.0, 6.0, 2.0);
	if(sum < 0.0007307305932044983 * factor)
		stage_sum += 0.5704951882362366;
	else
		stage_sum += 0.2321965992450714;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 6.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(4.0, 10.0, 6.0, 4.0, 2.0);
	if(sum < 0.0006404530140571296 * factor)
		stage_sum += 0.21122519671916962;
	else
		stage_sum += 0.5814933180809021;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 2.0, 8.0, 5.0, -1.0);
	sum += rect_sum_ii(12.0, 2.0, 4.0, 5.0, 2.0);
	if(sum < 0.004542401991784573 * factor)
		stage_sum += 0.29504820704460144;
	else
		stage_sum += 0.586631178855896;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 8.0, 18.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 9.0, 18.0, 1.0, 3.0);
	if(sum < 0.00009247744310414419 * factor)
		stage_sum += 0.2990990877151489;
	else
		stage_sum += 0.5791326761245728;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 4.0, 8.0, -1.0);
	sum += rect_sum_ii(8.0, 16.0, 4.0, 4.0, 2.0);
	if(sum < -0.008660314604640007 * factor)
		stage_sum += 0.2813029885292053;
	else
		stage_sum += 0.5635542273521423;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 8.0, 5.0, -1.0);
	sum += rect_sum_ii(4.0, 2.0, 4.0, 5.0, 2.0);
	if(sum < 0.008051581680774689 * factor)
		stage_sum += 0.3535369038581848;
	else
		stage_sum += 0.6054757237434387;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 11.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 13.0, 3.0, 2.0, 2.0);
	if(sum < 0.00043835240649059415 * factor)
		stage_sum += 0.5596532225608826;
	else
		stage_sum += 0.27315109968185425;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 11.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 11.0, 2.0, 1.0, 3.0);
	if(sum < -0.0000981689736363478 * factor)
		stage_sum += 0.5978031754493713;
	else
		stage_sum += 0.36385610699653625;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 3.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(12.0, 3.0, 1.0, 1.0, 3.0);
	if(sum < -0.0011298790341243148 * factor)
		stage_sum += 0.27552521228790283;
	else
		stage_sum += 0.5432729125022888;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 13.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 14.0, 5.0, 1.0, 3.0);
	if(sum < 0.006435615010559559 * factor)
		stage_sum += 0.43056419491767883;
	else
		stage_sum += 0.7069833278656006;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 11.0, 7.0, 6.0, -1.0);
	sum += rect_sum_ii(11.0, 14.0, 7.0, 3.0, 2.0);
	if(sum < -0.05682932958006859 * factor)
		stage_sum += 0.2495242953300476;
	else
		stage_sum += 0.5294997096061707;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 11.0, 7.0, 6.0, -1.0);
	sum += rect_sum_ii(2.0, 14.0, 7.0, 3.0, 2.0);
	if(sum < 0.004066816996783018 * factor)
		stage_sum += 0.5478553175926208;
	else
		stage_sum += 0.24977239966392517;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 14.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(12.0, 16.0, 2.0, 2.0, 3.0);
	if(sum < 0.0000481647984997835 * factor)
		stage_sum += 0.3938601016998291;
	else
		stage_sum += 0.5706356167793274;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 3.0, 1.0, 3.0);
	if(sum < 0.00617950176820159 * factor)
		stage_sum += 0.44076061248779297;
	else
		stage_sum += 0.7394766807556152;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 0.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(12.0, 0.0, 1.0, 5.0, 3.0);
	if(sum < 0.006498575210571289 * factor)
		stage_sum += 0.5445243120193481;
	else
		stage_sum += 0.24791529774665833;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 1.0, 4.0, 9.0, -1.0);
	sum += rect_sum_ii(8.0, 1.0, 2.0, 9.0, 2.0);
	if(sum < -0.0010211090557277203 * factor)
		stage_sum += 0.2544766962528229;
	else
		stage_sum += 0.5338971018791199;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 3.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(12.0, 3.0, 2.0, 1.0, 3.0);
	if(sum < -0.005424752831459045 * factor)
		stage_sum += 0.27188581228256226;
	else
		stage_sum += 0.5324069261550903;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 10.0, 3.0, 2.0, 2.0);
	if(sum < -0.0010559899965301156 * factor)
		stage_sum += 0.31782880425453186;
	else
		stage_sum += 0.553450882434845;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 13.0, 4.0, 1.0, 2.0);
	if(sum < 0.0006646580877713859 * factor)
		stage_sum += 0.42842191457748413;
	else
		stage_sum += 0.6558194160461426;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 18.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 19.0, 4.0, 1.0, 2.0);
	if(sum < -0.00027524109464138746 * factor)
		stage_sum += 0.5902860760688782;
	else
		stage_sum += 0.3810262978076935;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 1.0, 18.0, 6.0, -1.0);
	sum += rect_sum_ii(2.0, 3.0, 18.0, 2.0, 3.0);
	if(sum < 0.004229320213198662 * factor)
		stage_sum += 0.381648987531662;
	else
		stage_sum += 0.5709385871887207;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 0.0, 1.0, 2.0, 3.0);
	if(sum < -0.0032868210691958666 * factor)
		stage_sum += 0.1747743934392929;
	else
		stage_sum += 0.5259544253349304;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 8.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 8.0, 3.0, 1.0, 2.0);
	sum += rect_sum_ii(13.0, 9.0, 3.0, 1.0, 2.0);
	if(sum < 0.0001561187964398414 * factor)
		stage_sum += 0.36017221212387085;
	else
		stage_sum += 0.5725612044334412;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 10.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 13.0, 3.0, 3.0, 2.0);
	if(sum < -0.000007362138148891972 * factor)
		stage_sum += 0.540185809135437;
	else
		stage_sum += 0.3044497072696686;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 13.0, 20.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 13.0, 10.0, 2.0, 2.0);
	sum += rect_sum_ii(0.0, 15.0, 10.0, 2.0, 2.0);
	if(sum < -0.014767250046133995 * factor)
		stage_sum += 0.3220770061016083;
	else
		stage_sum += 0.5573434829711914;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 7.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 2.0, 5.0, 3.0);
	if(sum < 0.024489590898156166 * factor)
		stage_sum += 0.4301528036594391;
	else
		stage_sum += 0.6518812775611877;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 0.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 1.0, 2.0, 1.0, 2.0);
	if(sum < -0.000376520911231637 * factor)
		stage_sum += 0.35645830631256104;
	else
		stage_sum += 0.5598236918449402;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 8.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(1.0, 8.0, 3.0, 1.0, 2.0);
	sum += rect_sum_ii(4.0, 9.0, 3.0, 1.0, 2.0);
	if(sum < 0.00000736576885174145 * factor)
		stage_sum += 0.34907829761505127;
	else
		stage_sum += 0.556189775466919;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 20.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 2.0, 10.0, 1.0, 2.0);
	sum += rect_sum_ii(0.0, 3.0, 10.0, 1.0, 2.0);
	if(sum < -0.01509993989020586 * factor)
		stage_sum += 0.17762720584869385;
	else
		stage_sum += 0.5335299968719482;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 14.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 15.0, 5.0, 1.0, 3.0);
	if(sum < -0.0038316650316119194 * factor)
		stage_sum += 0.6149687767028809;
	else
		stage_sum += 0.42213940620422363;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 13.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 13.0, 3.0, 3.0, 2.0);
	sum += rect_sum_ii(7.0, 16.0, 3.0, 3.0, 2.0);
	if(sum < 0.016925400123000145 * factor)
		stage_sum += 0.5413014888763428;
	else
		stage_sum += 0.21665850281715393;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 12.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 13.0, 2.0, 1.0, 3.0);
	if(sum < -0.003047785023227334 * factor)
		stage_sum += 0.6449490785598755;
	else
		stage_sum += 0.43546178936958313;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 11.0, 1.0, 6.0, -1.0);
	sum += rect_sum_ii(16.0, 13.0, 1.0, 2.0, 3.0);
	if(sum < 0.003214058931916952 * factor)
		stage_sum += 0.5400155186653137;
	else
		stage_sum += 0.35232171416282654;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 11.0, 1.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 13.0, 1.0, 2.0, 3.0);
	if(sum < -0.004002320114523172 * factor)
		stage_sum += 0.27745240926742554;
	else
		stage_sum += 0.5338417291641235;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 14.0, 12.0, -1.0);
	sum += rect_sum_ii(11.0, 4.0, 7.0, 6.0, 2.0);
	sum += rect_sum_ii(4.0, 10.0, 7.0, 6.0, 2.0);
	if(sum < 0.0074182129465043545 * factor)
		stage_sum += 0.567673921585083;
	else
		stage_sum += 0.37028178572654724;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 5.0, 3.0, 1.0, 3.0);
	if(sum < -0.008876458741724491 * factor)
		stage_sum += 0.7749221920967102;
	else
		stage_sum += 0.4583688974380493;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 3.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 3.0, 1.0, 3.0, 3.0);
	if(sum < 0.002731173997744918 * factor)
		stage_sum += 0.5338721871376038;
	else
		stage_sum += 0.39966610074043274;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 7.0, 8.0, 1.0, 3.0);
	if(sum < -0.0025082379579544067 * factor)
		stage_sum += 0.5611963272094727;
	else
		stage_sum += 0.37774989008903503;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 3.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 3.0, 1.0, 3.0, 3.0);
	if(sum < -0.008054107427597046 * factor)
		stage_sum += 0.29152289032936096;
	else
		stage_sum += 0.5179182887077332;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 1.0, 4.0, 10.0, -1.0);
	sum += rect_sum_ii(3.0, 1.0, 2.0, 5.0, 2.0);
	sum += rect_sum_ii(5.0, 6.0, 2.0, 5.0, 2.0);
	if(sum < -0.0009793881326913834 * factor)
		stage_sum += 0.5536432862281799;
	else
		stage_sum += 0.3700192868709564;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 10.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 7.0, 5.0, 2.0, 2.0);
	if(sum < -0.005874590948224068 * factor)
		stage_sum += 0.3754391074180603;
	else
		stage_sum += 0.5679376125335693;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 7.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 1.0, 3.0, 3.0);
	if(sum < -0.00449367193505168 * factor)
		stage_sum += 0.7019699215888977;
	else
		stage_sum += 0.4480949938297272;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 12.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 13.0, 2.0, 1.0, 3.0);
	if(sum < -0.00543892290443182 * factor)
		stage_sum += 0.2310364991426468;
	else
		stage_sum += 0.5313386917114258;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 8.0, 1.0, 4.0, 3.0);
	if(sum < -0.0007509464048780501 * factor)
		stage_sum += 0.5864868760108948;
	else
		stage_sum += 0.4129343032836914;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 4.0, 1.0, 12.0, -1.0);
	sum += rect_sum_ii(13.0, 10.0, 1.0, 6.0, 2.0);
	if(sum < 0.000014528800420521293 * factor)
		stage_sum += 0.37324070930480957;
	else
		stage_sum += 0.5619621276855469;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 5.0, 12.0, 12.0, -1.0);
	sum += rect_sum_ii(4.0, 5.0, 6.0, 6.0, 2.0);
	sum += rect_sum_ii(10.0, 11.0, 6.0, 6.0, 2.0);
	if(sum < 0.04075806960463524 * factor)
		stage_sum += 0.5312091112136841;
	else
		stage_sum += 0.27205219864845276;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 14.0, 7.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 15.0, 7.0, 1.0, 3.0);
	if(sum < 0.006650593131780624 * factor)
		stage_sum += 0.47100159525871277;
	else
		stage_sum += 0.6693493723869324;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 12.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 13.0, 2.0, 1.0, 3.0);
	if(sum < 0.0045759351924061775 * factor)
		stage_sum += 0.5167819261550903;
	else
		stage_sum += 0.16372759640216827;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 2.0, 14.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 2.0, 7.0, 1.0, 2.0);
	sum += rect_sum_ii(3.0, 3.0, 7.0, 1.0, 2.0);
	if(sum < 0.0065269311890006065 * factor)
		stage_sum += 0.5397608876228333;
	else
		stage_sum += 0.29385319352149963;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 1.0, 3.0, 10.0, -1.0);
	sum += rect_sum_ii(1.0, 1.0, 1.0, 10.0, 3.0);
	if(sum < -0.013660379685461521 * factor)
		stage_sum += 0.7086488008499146;
	else
		stage_sum += 0.453220009803772;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 0.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(11.0, 0.0, 2.0, 5.0, 3.0);
	if(sum < 0.027358869090676308 * factor)
		stage_sum += 0.5206481218338013;
	else
		stage_sum += 0.35892319679260254;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 3.0, 2.0, 2.0);
	if(sum < 0.0006219755159690976 * factor)
		stage_sum += 0.3507075905799866;
	else
		stage_sum += 0.5441123247146606;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 1.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(7.0, 6.0, 6.0, 5.0, 2.0);
	if(sum < -0.0033077080734074116 * factor)
		stage_sum += 0.5859522819519043;
	else
		stage_sum += 0.40248918533325195;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 1.0, 18.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 1.0, 6.0, 3.0, 3.0);
	if(sum < -0.010631109587848186 * factor)
		stage_sum += 0.6743267178535461;
	else
		stage_sum += 0.4422602951526642;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 3.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(16.0, 5.0, 3.0, 2.0, 3.0);
	if(sum < 0.019441649317741394 * factor)
		stage_sum += 0.5282716155052185;
	else
		stage_sum += 0.17979049682617188;


	if(stage_sum > 27.153350830078125)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage9(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 3.0, 7.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 6.0, 7.0, 3.0, 2.0);
	if(sum < -0.005505216773599386 * factor)
		stage_sum += 0.5914731025695801;
	else
		stage_sum += 0.26265591382980347;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 7.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 4.0, 2.0, 3.0);
	if(sum < 0.001956227933987975 * factor)
		stage_sum += 0.23125819861888885;
	else
		stage_sum += 0.5741627216339111;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 4.0, 17.0, 10.0, -1.0);
	sum += rect_sum_ii(0.0, 9.0, 17.0, 5.0, 2.0);
	if(sum < -0.008892478421330452 * factor)
		stage_sum += 0.16565300524234772;
	else
		stage_sum += 0.5626654028892517;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 4.0, 15.0, 16.0, -1.0);
	sum += rect_sum_ii(3.0, 12.0, 15.0, 8.0, 2.0);
	if(sum < 0.08363837748765945 * factor)
		stage_sum += 0.5423449873924255;
	else
		stage_sum += 0.19572949409484863;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 15.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 17.0, 6.0, 2.0, 2.0);
	if(sum < 0.0012282270472496748 * factor)
		stage_sum += 0.34179040789604187;
	else
		stage_sum += 0.5992503762245178;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 2.0, 4.0, 9.0, -1.0);
	sum += rect_sum_ii(15.0, 2.0, 2.0, 9.0, 2.0);
	if(sum < 0.0057629169896245 * factor)
		stage_sum += 0.3719581961631775;
	else
		stage_sum += 0.6079903841018677;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 3.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 4.0, 3.0, 1.0, 2.0);
	if(sum < -0.0016417410224676132 * factor)
		stage_sum += 0.2577486038208008;
	else
		stage_sum += 0.5576915740966797;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 6.0, 7.0, 9.0, -1.0);
	sum += rect_sum_ii(13.0, 9.0, 7.0, 3.0, 3.0);
	if(sum < 0.0034113149158656597 * factor)
		stage_sum += 0.2950749099254608;
	else
		stage_sum += 0.5514171719551086;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 11.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 12.0, 4.0, 1.0, 3.0);
	if(sum < -0.011069320142269135 * factor)
		stage_sum += 0.7569358944892883;
	else
		stage_sum += 0.4477078914642334;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 20.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 2.0, 10.0, 3.0, 2.0);
	sum += rect_sum_ii(0.0, 5.0, 10.0, 3.0, 2.0);
	if(sum < 0.03486597165465355 * factor)
		stage_sum += 0.5583708882331848;
	else
		stage_sum += 0.26696211099624634;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 2.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(3.0, 2.0, 3.0, 5.0, 2.0);
	sum += rect_sum_ii(6.0, 7.0, 3.0, 5.0, 2.0);
	if(sum < 0.0006570109981112182 * factor)
		stage_sum += 0.5627313256263733;
	else
		stage_sum += 0.29888901114463806;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 10.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 12.0, 3.0, 2.0, 2.0);
	if(sum < -0.024339130148291588 * factor)
		stage_sum += 0.2771185040473938;
	else
		stage_sum += 0.5108863115310669;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 10.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(4.0, 12.0, 3.0, 2.0, 2.0);
	if(sum < 0.0005943520227447152 * factor)
		stage_sum += 0.5580651760101318;
	else
		stage_sum += 0.3120341897010803;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 5.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 2.0, 3.0, 3.0);
	if(sum < 0.0022971509024500847 * factor)
		stage_sum += 0.3330250084400177;
	else
		stage_sum += 0.5679075717926025;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(7.0, 10.0, 6.0, 4.0, 2.0);
	if(sum < -0.0037801829166710377 * factor)
		stage_sum += 0.29905349016189575;
	else
		stage_sum += 0.5344808101654053;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 11.0, 20.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 20.0, 3.0, 2.0);
	if(sum < -0.13420669734477997 * factor)
		stage_sum += 0.14638589322566986;
	else
		stage_sum += 0.5392568111419678;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 13.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(4.0, 13.0, 2.0, 3.0, 2.0);
	sum += rect_sum_ii(6.0, 16.0, 2.0, 3.0, 2.0);
	if(sum < 0.0007522454834543169 * factor)
		stage_sum += 0.37469539046287537;
	else
		stage_sum += 0.5692734718322754;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 8.0, 12.0, -1.0);
	sum += rect_sum_ii(10.0, 0.0, 4.0, 6.0, 2.0);
	sum += rect_sum_ii(6.0, 6.0, 4.0, 6.0, 2.0);
	if(sum < -0.040545541793107986 * factor)
		stage_sum += 0.27547478675842285;
	else
		stage_sum += 0.5484297871589661;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 0.0, 15.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 1.0, 15.0, 1.0, 2.0);
	if(sum < 0.0012572970008477569 * factor)
		stage_sum += 0.3744584023952484;
	else
		stage_sum += 0.5756075978279114;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 12.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 13.0, 2.0, 1.0, 3.0);
	if(sum < -0.007424994837492704 * factor)
		stage_sum += 0.7513859272003174;
	else
		stage_sum += 0.4728231132030487;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 12.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(3.0, 13.0, 1.0, 1.0, 2.0);
	if(sum < 0.0005090812919661403 * factor)
		stage_sum += 0.540489673614502;
	else
		stage_sum += 0.29323211312294006;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 11.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 12.0, 2.0, 1.0, 3.0);
	if(sum < -0.001280845026485622 * factor)
		stage_sum += 0.6169779896736145;
	else
		stage_sum += 0.42733490467071533;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 3.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(8.0, 3.0, 1.0, 1.0, 3.0);
	if(sum < -0.0018348860321566463 * factor)
		stage_sum += 0.20484960079193115;
	else
		stage_sum += 0.5206472277641296;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(17.0, 9.0, 3.0, 2.0, 3.0);
	if(sum < 0.027484869584441185 * factor)
		stage_sum += 0.5252984762191772;
	else
		stage_sum += 0.16755220293998718;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 2.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 2.0, 1.0, 2.0, 3.0);
	if(sum < 0.0022372419480234385 * factor)
		stage_sum += 0.5267782807350159;
	else
		stage_sum += 0.27776581048965454;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 4.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 5.0, 5.0, 1.0, 3.0);
	if(sum < -0.008863529190421104 * factor)
		stage_sum += 0.69545578956604;
	else
		stage_sum += 0.48120489716529846;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 5.0, 5.0, 1.0, 3.0);
	if(sum < 0.004175397101789713 * factor)
		stage_sum += 0.4291887879371643;
	else
		stage_sum += 0.6349195837974548;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 3.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(19.0, 4.0, 1.0, 1.0, 2.0);
	if(sum < -0.0017098189564421773 * factor)
		stage_sum += 0.29305368661880493;
	else
		stage_sum += 0.5361248850822449;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 4.0, 1.0, 3.0);
	if(sum < 0.006532854866236448 * factor)
		stage_sum += 0.44953250885009766;
	else
		stage_sum += 0.7409694194793701;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(17.0, 9.0, 3.0, 2.0, 3.0);
	if(sum < -0.009537290781736374 * factor)
		stage_sum += 0.31491199135780334;
	else
		stage_sum += 0.5416501760482788;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 9.0, 3.0, 2.0, 3.0);
	if(sum < 0.02531098946928978 * factor)
		stage_sum += 0.5121892094612122;
	else
		stage_sum += 0.13117079436779022;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 2.0, 6.0, 9.0, -1.0);
	sum += rect_sum_ii(14.0, 5.0, 6.0, 3.0, 3.0);
	if(sum < 0.03646096959710121 * factor)
		stage_sum += 0.5175911784172058;
	else
		stage_sum += 0.2591339945793152;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 4.0, 5.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 6.0, 5.0, 2.0, 3.0);
	if(sum < 0.02085432969033718 * factor)
		stage_sum += 0.5137140154838562;
	else
		stage_sum += 0.15823160111904144;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 5.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 5.0, 2.0, 2.0, 3.0);
	if(sum < -0.0008720774785615504 * factor)
		stage_sum += 0.5574309825897217;
	else
		stage_sum += 0.43989789485931396;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 5.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 5.0, 2.0, 2.0, 3.0);
	if(sum < -0.000015227000403683633 * factor)
		stage_sum += 0.5548940896987915;
	else
		stage_sum += 0.3708069920539856;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 1.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 3.0, 4.0, 2.0, 3.0);
	if(sum < -0.0008431650931015611 * factor)
		stage_sum += 0.3387419879436493;
	else
		stage_sum += 0.5554211139678955;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 4.0, 3.0, 2.0, 3.0);
	if(sum < 0.0036037859972566366 * factor)
		stage_sum += 0.5358061790466309;
	else
		stage_sum += 0.34111711382865906;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 7.0, 8.0, 1.0, 3.0);
	if(sum < -0.006805789191275835 * factor)
		stage_sum += 0.6125202775001526;
	else
		stage_sum += 0.4345862865447998;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 1.0, 5.0, 9.0, -1.0);
	sum += rect_sum_ii(0.0, 4.0, 5.0, 3.0, 3.0);
	if(sum < -0.04702166095376015 * factor)
		stage_sum += 0.2358165979385376;
	else
		stage_sum += 0.519373893737793;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 0.0, 4.0, 15.0, -1.0);
	sum += rect_sum_ii(16.0, 0.0, 2.0, 15.0, 2.0);
	if(sum < -0.036954108625650406 * factor)
		stage_sum += 0.7323111295700073;
	else
		stage_sum += 0.47609439492225647;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 10.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(1.0, 11.0, 3.0, 1.0, 2.0);
	if(sum < 0.0010439479956403375 * factor)
		stage_sum += 0.5419455170631409;
	else
		stage_sum += 0.34113308787345886;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 4.0, 1.0, 10.0, -1.0);
	sum += rect_sum_ii(14.0, 9.0, 1.0, 5.0, 2.0);
	if(sum < -0.00021050689974799752 * factor)
		stage_sum += 0.2821694016456604;
	else
		stage_sum += 0.5554947257041931;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 1.0, 4.0, 12.0, -1.0);
	sum += rect_sum_ii(2.0, 1.0, 2.0, 12.0, 2.0);
	if(sum < -0.08083158731460571 * factor)
		stage_sum += 0.9129930138587952;
	else
		stage_sum += 0.4697434902191162;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 11.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 11.0, 2.0, 2.0, 2.0);
	if(sum < -0.0003657905908767134 * factor)
		stage_sum += 0.6022670269012451;
	else
		stage_sum += 0.3978292942047119;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 11.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 11.0, 2.0, 2.0, 2.0);
	if(sum < -0.00012545920617412776 * factor)
		stage_sum += 0.5613213181495667;
	else
		stage_sum += 0.384553998708725;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 8.0, 15.0, 5.0, -1.0);
	sum += rect_sum_ii(8.0, 8.0, 5.0, 5.0, 3.0);
	if(sum < -0.06878648698329926 * factor)
		stage_sum += 0.2261611968278885;
	else
		stage_sum += 0.5300496816635132;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(3.0, 0.0, 3.0, 10.0, 2.0);
	if(sum < 0.012415789999067783 * factor)
		stage_sum += 0.40756919980049133;
	else
		stage_sum += 0.5828812122344971;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 4.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 4.0, 1.0, 2.0, 3.0);
	if(sum < -0.004717481788247824 * factor)
		stage_sum += 0.28272539377212524;
	else
		stage_sum += 0.5267757773399353;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 3.0, 8.0, -1.0);
	sum += rect_sum_ii(8.0, 16.0, 3.0, 4.0, 2.0);
	if(sum < 0.038136858493089676 * factor)
		stage_sum += 0.5074741244316101;
	else
		stage_sum += 0.10236159712076187;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 5.0, 1.0, 3.0);
	if(sum < -0.0028168049175292253 * factor)
		stage_sum += 0.6169006824493408;
	else
		stage_sum += 0.4359692931175232;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 14.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 15.0, 4.0, 1.0, 3.0);
	if(sum < 0.008130360394716263 * factor)
		stage_sum += 0.45244330167770386;
	else
		stage_sum += 0.76060950756073;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 4.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 4.0, 1.0, 2.0, 3.0);
	if(sum < 0.006005601957440376 * factor)
		stage_sum += 0.5240408778190613;
	else
		stage_sum += 0.185971200466156;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 15.0, 14.0, 4.0, -1.0);
	sum += rect_sum_ii(3.0, 15.0, 7.0, 2.0, 2.0);
	sum += rect_sum_ii(10.0, 17.0, 7.0, 2.0, 2.0);
	if(sum < 0.01913931965827942 * factor)
		stage_sum += 0.5209379196166992;
	else
		stage_sum += 0.23320719599723816;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 2.0, 16.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 2.0, 8.0, 2.0, 2.0);
	sum += rect_sum_ii(2.0, 4.0, 8.0, 2.0, 2.0);
	if(sum < 0.016445759683847427 * factor)
		stage_sum += 0.5450702905654907;
	else
		stage_sum += 0.3264234960079193;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 8.0, 6.0, 12.0, -1.0);
	sum += rect_sum_ii(3.0, 8.0, 3.0, 12.0, 2.0);
	if(sum < -0.037356890738010406 * factor)
		stage_sum += 0.6999046802520752;
	else
		stage_sum += 0.45332419872283936;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 10.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 7.0, 5.0, 2.0, 2.0);
	if(sum < -0.019727900624275208 * factor)
		stage_sum += 0.26536649465560913;
	else
		stage_sum += 0.54128098487854;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 2.0, 5.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 5.0, 2.0);
	if(sum < 0.0066972579807043076 * factor)
		stage_sum += 0.4480566084384918;
	else
		stage_sum += 0.7138652205467224;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 7.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(16.0, 7.0, 3.0, 2.0, 2.0);
	sum += rect_sum_ii(13.0, 9.0, 3.0, 2.0, 2.0);
	if(sum < 0.0007445752853527665 * factor)
		stage_sum += 0.42313501238822937;
	else
		stage_sum += 0.5471320152282715;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 13.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 8.0, 1.0, 2.0);
	if(sum < 0.0011790640419349074 * factor)
		stage_sum += 0.5341702103614807;
	else
		stage_sum += 0.3130455017089844;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 7.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(16.0, 7.0, 3.0, 2.0, 2.0);
	sum += rect_sum_ii(13.0, 9.0, 3.0, 2.0, 2.0);
	if(sum < 0.03498061001300812 * factor)
		stage_sum += 0.5118659734725952;
	else
		stage_sum += 0.34305301308631897;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(1.0, 7.0, 3.0, 2.0, 2.0);
	sum += rect_sum_ii(4.0, 9.0, 3.0, 2.0, 2.0);
	if(sum < 0.0005685979267582297 * factor)
		stage_sum += 0.3532187044620514;
	else
		stage_sum += 0.5468639731407166;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 6.0, 1.0, 12.0, -1.0);
	sum += rect_sum_ii(12.0, 12.0, 1.0, 6.0, 2.0);
	if(sum < -0.011340649798512459 * factor)
		stage_sum += 0.2842353880405426;
	else
		stage_sum += 0.5348700881004333;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 5.0, 1.0, 6.0, 2.0);
	if(sum < -0.00662281084805727 * factor)
		stage_sum += 0.6883640289306641;
	else
		stage_sum += 0.4492664933204651;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 12.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(14.0, 13.0, 2.0, 1.0, 3.0);
	if(sum < -0.008016033098101616 * factor)
		stage_sum += 0.17098939418792725;
	else
		stage_sum += 0.5224308967590332;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 12.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 13.0, 2.0, 1.0, 3.0);
	if(sum < 0.0014206819469109178 * factor)
		stage_sum += 0.5290846228599548;
	else
		stage_sum += 0.29933831095695496;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 13.0, 4.0, 1.0, 3.0);
	if(sum < -0.002780171111226082 * factor)
		stage_sum += 0.6498854160308838;
	else
		stage_sum += 0.4460499882698059;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 2.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(5.0, 2.0, 1.0, 2.0, 2.0);
	sum += rect_sum_ii(6.0, 4.0, 1.0, 2.0, 2.0);
	if(sum < -0.0014747589593753219 * factor)
		stage_sum += 0.3260438144207001;
	else
		stage_sum += 0.5388113260269165;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 11.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 11.0, 1.0, 3.0);
	if(sum < -0.023830339312553406 * factor)
		stage_sum += 0.7528941035270691;
	else
		stage_sum += 0.48012199997901917;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 4.0, 12.0, -1.0);
	sum += rect_sum_ii(7.0, 12.0, 4.0, 6.0, 2.0);
	if(sum < 0.00693697901442647 * factor)
		stage_sum += 0.5335165858268738;
	else
		stage_sum += 0.3261427879333496;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 13.0, 8.0, 5.0, -1.0);
	sum += rect_sum_ii(12.0, 13.0, 4.0, 5.0, 2.0);
	if(sum < 0.008280625566840172 * factor)
		stage_sum += 0.45803940296173096;
	else
		stage_sum += 0.5737829804420471;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 1.0, 12.0, -1.0);
	sum += rect_sum_ii(7.0, 12.0, 1.0, 6.0, 2.0);
	if(sum < -0.010439500212669373 * factor)
		stage_sum += 0.2592320144176483;
	else
		stage_sum += 0.5233827829360962;


	if(stage_sum > 34.55411148071289)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage10(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 2.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 2.0, 3.0, 3.0, 2.0);
	if(sum < 0.0072006587870419025 * factor)
		stage_sum += 0.32588860392570496;
	else
		stage_sum += 0.6849808096885681;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(12.0, 5.0, 3.0, 5.0, 2.0);
	sum += rect_sum_ii(9.0, 10.0, 3.0, 5.0, 2.0);
	if(sum < -0.002859358908608556 * factor)
		stage_sum += 0.5838881134986877;
	else
		stage_sum += 0.2537829875946045;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 8.0, 12.0, -1.0);
	sum += rect_sum_ii(5.0, 5.0, 4.0, 6.0, 2.0);
	sum += rect_sum_ii(9.0, 11.0, 4.0, 6.0, 2.0);
	if(sum < 0.0006858052802272141 * factor)
		stage_sum += 0.5708081722259521;
	else
		stage_sum += 0.28124240040779114;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 7.0, 20.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 9.0, 20.0, 2.0, 3.0);
	if(sum < 0.007958019152283669 * factor)
		stage_sum += 0.2501051127910614;
	else
		stage_sum += 0.5544260740280151;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 2.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(4.0, 3.0, 2.0, 1.0, 2.0);
	if(sum < -0.0012124150525778532 * factor)
		stage_sum += 0.2385368049144745;
	else
		stage_sum += 0.5433350205421448;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 18.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 18.0, 4.0, 2.0, 3.0);
	if(sum < 0.00794261321425438 * factor)
		stage_sum += 0.3955070972442627;
	else
		stage_sum += 0.6220757961273193;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 4.0, 4.0, 16.0, -1.0);
	sum += rect_sum_ii(7.0, 12.0, 4.0, 8.0, 2.0);
	if(sum < 0.0024630590341985226 * factor)
		stage_sum += 0.5639708042144775;
	else
		stage_sum += 0.2992357909679413;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 7.0, 8.0, -1.0);
	sum += rect_sum_ii(7.0, 10.0, 7.0, 4.0, 2.0);
	if(sum < -0.006039659958332777 * factor)
		stage_sum += 0.21865129470825195;
	else
		stage_sum += 0.541167676448822;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 3.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 3.0, 1.0, 1.0, 3.0);
	if(sum < -0.0012988339876756072 * factor)
		stage_sum += 0.23507060110569;
	else
		stage_sum += 0.5364584922790527;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 15.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 17.0, 2.0, 2.0, 2.0);
	if(sum < 0.00022299369447864592 * factor)
		stage_sum += 0.380411297082901;
	else
		stage_sum += 0.572960615158081;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 5.0, 4.0, 8.0, -1.0);
	sum += rect_sum_ii(3.0, 9.0, 4.0, 4.0, 2.0);
	if(sum < 0.0014654280385002494 * factor)
		stage_sum += 0.2510167956352234;
	else
		stage_sum += 0.5258268713951111;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 1.0, 6.0, 12.0, -1.0);
	sum += rect_sum_ii(7.0, 7.0, 6.0, 6.0, 2.0);
	if(sum < -0.0008121004211716354 * factor)
		stage_sum += 0.5992823839187622;
	else
		stage_sum += 0.3851158916950226;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 6.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 6.0, 2.0, 2.0, 3.0);
	if(sum < -0.0013836020370945334 * factor)
		stage_sum += 0.5681396126747131;
	else
		stage_sum += 0.36365869641304016;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 4.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(16.0, 6.0, 4.0, 2.0, 3.0);
	if(sum < -0.027936449274420738 * factor)
		stage_sum += 0.14913170039653778;
	else
		stage_sum += 0.5377560257911682;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 3.0, 5.0, 2.0, -1.0);
	sum += rect_sum_ii(3.0, 4.0, 5.0, 1.0, 2.0);
	if(sum < -0.0004691955109592527 * factor)
		stage_sum += 0.36924299597740173;
	else
		stage_sum += 0.5572484731674194;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 11.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 12.0, 2.0, 1.0, 3.0);
	if(sum < -0.004982965998351574 * factor)
		stage_sum += 0.6758509278297424;
	else
		stage_sum += 0.4532504081726074;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 16.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 17.0, 4.0, 1.0, 2.0);
	if(sum < 0.001881530974060297 * factor)
		stage_sum += 0.5368022918701172;
	else
		stage_sum += 0.29325398802757263;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 13.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 13.0, 3.0, 3.0, 2.0);
	sum += rect_sum_ii(7.0, 16.0, 3.0, 3.0, 2.0);
	if(sum < -0.0190675500780344 * factor)
		stage_sum += 0.16493770480155945;
	else
		stage_sum += 0.5330067276954651;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 0.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 0.0, 1.0, 4.0, 3.0);
	if(sum < -0.0046906559728085995 * factor)
		stage_sum += 0.19639259576797485;
	else
		stage_sum += 0.5119361877441406;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 15.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 16.0, 4.0, 1.0, 3.0);
	if(sum < 0.005977713968604803 * factor)
		stage_sum += 0.46711719036102295;
	else
		stage_sum += 0.7008398175239563;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 4.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 6.0, 4.0, 2.0, 3.0);
	if(sum < -0.03330313041806221 * factor)
		stage_sum += 0.11554169654846191;
	else
		stage_sum += 0.5104162096977234;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 12.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 4.0, 3.0, 3.0);
	if(sum < 0.09074410796165466 * factor)
		stage_sum += 0.5149660110473633;
	else
		stage_sum += 0.13061730563640594;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 6.0, 14.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 2.0, 14.0, 3.0);
	if(sum < 0.0009355589863844216 * factor)
		stage_sum += 0.36054810881614685;
	else
		stage_sum += 0.543985903263092;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 3.0, 3.0);
	if(sum < 0.01490165013819933 * factor)
		stage_sum += 0.48862120509147644;
	else
		stage_sum += 0.7687569856643677;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 12.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(6.0, 14.0, 2.0, 2.0, 2.0);
	if(sum < 0.0006159411859698594 * factor)
		stage_sum += 0.5356813073158264;
	else
		stage_sum += 0.32409390807151794;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 12.0, 7.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 14.0, 7.0, 2.0, 3.0);
	if(sum < -0.050670988857746124 * factor)
		stage_sum += 0.1848621964454651;
	else
		stage_sum += 0.5230404138565063;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 15.0, 2.0, -1.0);
	sum += rect_sum_ii(1.0, 1.0, 15.0, 1.0, 2.0);
	if(sum < 0.0006866574985906482 * factor)
		stage_sum += 0.38405799865722656;
	else
		stage_sum += 0.5517945885658264;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 0.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(14.0, 0.0, 3.0, 6.0, 2.0);
	if(sum < 0.008371243253350258 * factor)
		stage_sum += 0.42885640263557434;
	else
		stage_sum += 0.6131753921508789;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 3.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(6.0, 3.0, 1.0, 1.0, 3.0);
	if(sum < -0.0012953069526702166 * factor)
		stage_sum += 0.29136741161346436;
	else
		stage_sum += 0.528073787689209;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 0.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(14.0, 0.0, 3.0, 6.0, 2.0);
	if(sum < -0.04194168001413345 * factor)
		stage_sum += 0.7554799914360046;
	else
		stage_sum += 0.48560309410095215;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 3.0, 20.0, 10.0, -1.0);
	sum += rect_sum_ii(0.0, 8.0, 20.0, 5.0, 2.0);
	if(sum < -0.023529380559921265 * factor)
		stage_sum += 0.2838279902935028;
	else
		stage_sum += 0.5256081223487854;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 0.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(14.0, 0.0, 3.0, 6.0, 2.0);
	if(sum < 0.04085744917392731 * factor)
		stage_sum += 0.4870935082435608;
	else
		stage_sum += 0.6277297139167786;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 0.0, 3.0, 6.0, 2.0);
	if(sum < -0.025406869128346443 * factor)
		stage_sum += 0.7099707722663879;
	else
		stage_sum += 0.45750290155410767;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 15.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(19.0, 16.0, 1.0, 1.0, 2.0);
	if(sum < -0.00041415440500713885 * factor)
		stage_sum += 0.40308868885040283;
	else
		stage_sum += 0.5469412207603455;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 4.0, 8.0, -1.0);
	sum += rect_sum_ii(2.0, 2.0, 2.0, 8.0, 2.0);
	if(sum < 0.021824119612574577 * factor)
		stage_sum += 0.45020240545272827;
	else
		stage_sum += 0.6768701076507568;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 1.0, 18.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 1.0, 9.0, 2.0, 2.0);
	sum += rect_sum_ii(2.0, 3.0, 9.0, 2.0, 2.0);
	if(sum < 0.014114039950072765 * factor)
		stage_sum += 0.5442860722541809;
	else
		stage_sum += 0.3791700005531311;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 13.0, 1.0, 1.0, 2.0);
	if(sum < 0.00006721459067193791 * factor)
		stage_sum += 0.4200463891029358;
	else
		stage_sum += 0.5873476266860962;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 2.0, 10.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 2.0, 5.0, 3.0, 2.0);
	sum += rect_sum_ii(5.0, 5.0, 5.0, 3.0, 2.0);
	if(sum < -0.00794176384806633 * factor)
		stage_sum += 0.3792561888694763;
	else
		stage_sum += 0.5585265755653381;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 4.0, 2.0);
	if(sum < -0.00721444096416235 * factor)
		stage_sum += 0.7253103852272034;
	else
		stage_sum += 0.46035489439964294;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 3.0, 3.0);
	if(sum < 0.002581733977422118 * factor)
		stage_sum += 0.46933019161224365;
	else
		stage_sum += 0.5900238752365112;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 5.0, 12.0, 8.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 4.0, 8.0, 3.0);
	if(sum < 0.13409319519996643 * factor)
		stage_sum += 0.5149213075637817;
	else
		stage_sum += 0.1808844953775406;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 15.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 16.0, 4.0, 1.0, 3.0);
	if(sum < 0.0022962710354477167 * factor)
		stage_sum += 0.5399743914604187;
	else
		stage_sum += 0.3717867136001587;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 18.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < -0.002157584996894002 * factor)
		stage_sum += 0.2408495992422104;
	else
		stage_sum += 0.5148863792419434;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 13.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 14.0, 4.0, 1.0, 3.0);
	if(sum < -0.004919618833810091 * factor)
		stage_sum += 0.6573588252067566;
	else
		stage_sum += 0.4738740026950836;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 13.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 14.0, 4.0, 1.0, 3.0);
	if(sum < 0.0016267469618469477 * factor)
		stage_sum += 0.4192821979522705;
	else
		stage_sum += 0.6303114295005798;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 15.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(19.0, 16.0, 1.0, 1.0, 2.0);
	if(sum < 0.00033413388882763684 * factor)
		stage_sum += 0.5540298223495483;
	else
		stage_sum += 0.37021011114120483;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 15.0, 8.0, 4.0, -1.0);
	sum += rect_sum_ii(0.0, 17.0, 8.0, 2.0, 2.0);
	if(sum < -0.026698080822825432 * factor)
		stage_sum += 0.17109179496765137;
	else
		stage_sum += 0.5101410746574402;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 3.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 3.0, 2.0, 4.0, 3.0);
	if(sum < -0.03056187927722931 * factor)
		stage_sum += 0.19042180478572845;
	else
		stage_sum += 0.5168793797492981;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 4.0, 1.0, 3.0);
	if(sum < 0.002851154888048768 * factor)
		stage_sum += 0.44475069642066956;
	else
		stage_sum += 0.6313853859901428;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 14.0, 14.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 16.0, 14.0, 2.0, 3.0);
	if(sum < -0.03621147945523262 * factor)
		stage_sum += 0.24907270073890686;
	else
		stage_sum += 0.5377349257469177;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 3.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 6.0, 6.0, 3.0, 2.0);
	if(sum < -0.002411518944427371 * factor)
		stage_sum += 0.5381243228912354;
	else
		stage_sum += 0.36642369627952576;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 11.0, 10.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 14.0, 10.0, 3.0, 2.0);
	if(sum < -0.0007725320174358785 * factor)
		stage_sum += 0.5530232191085815;
	else
		stage_sum += 0.3541550040245056;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 10.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(4.0, 10.0, 1.0, 4.0, 3.0);
	if(sum < 0.0002948172914329916 * factor)
		stage_sum += 0.41326990723609924;
	else
		stage_sum += 0.5667243003845215;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 9.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(13.0, 9.0, 1.0, 2.0, 2.0);
	if(sum < -0.006233456078916788 * factor)
		stage_sum += 0.09878723323345184;
	else
		stage_sum += 0.5198668837547302;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 3.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 3.0, 2.0, 4.0, 3.0);
	if(sum < -0.026274729520082474 * factor)
		stage_sum += 0.09112749248743057;
	else
		stage_sum += 0.5028107166290283;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 3.0, 3.0);
	if(sum < 0.005321226082742214 * factor)
		stage_sum += 0.47266489267349243;
	else
		stage_sum += 0.6222720742225647;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 12.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(2.0, 13.0, 2.0, 1.0, 3.0);
	if(sum < -0.004112905822694302 * factor)
		stage_sum += 0.2157457023859024;
	else
		stage_sum += 0.5137804746627808;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 8.0, 3.0, 12.0, -1.0);
	sum += rect_sum_ii(9.0, 12.0, 3.0, 4.0, 3.0);
	if(sum < 0.0032457809429615736 * factor)
		stage_sum += 0.5410770773887634;
	else
		stage_sum += 0.37217769026756287;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 14.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 14.0, 2.0, 3.0, 2.0);
	sum += rect_sum_ii(5.0, 17.0, 2.0, 3.0, 2.0);
	if(sum < -0.016359709203243256 * factor)
		stage_sum += 0.7787874937057495;
	else
		stage_sum += 0.46852919459342957;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 15.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 16.0, 2.0, 1.0, 2.0);
	if(sum < 0.00032166109303943813 * factor)
		stage_sum += 0.5478987097740173;
	else
		stage_sum += 0.4240373969078064;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 15.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 16.0, 2.0, 1.0, 2.0);
	if(sum < 0.000644524407107383 * factor)
		stage_sum += 0.5330560803413391;
	else
		stage_sum += 0.3501324951648712;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 13.0, 4.0, 1.0, 3.0);
	if(sum < -0.0078909732401371 * factor)
		stage_sum += 0.6923521161079407;
	else
		stage_sum += 0.47265690565109253;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 7.0, 20.0, 1.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 10.0, 1.0, 2.0);
	if(sum < 0.048336211591959 * factor)
		stage_sum += 0.50559002161026;
	else
		stage_sum += 0.07574920356273651;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 6.0, 4.0, 3.0, 2.0);
	if(sum < -0.000751781277358532 * factor)
		stage_sum += 0.3783741891384125;
	else
		stage_sum += 0.5538573861122131;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 4.0, 2.0, 2.0);
	if(sum < -0.002495391061529517 * factor)
		stage_sum += 0.3081651031970978;
	else
		stage_sum += 0.5359612107276917;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 5.0, 3.0);
	if(sum < -0.0022385010961443186 * factor)
		stage_sum += 0.663395881652832;
	else
		stage_sum += 0.4649342894554138;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 7.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 1.0, 5.0, 3.0);
	if(sum < -0.0017988430336117744 * factor)
		stage_sum += 0.6596844792366028;
	else
		stage_sum += 0.4347187876701355;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 1.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(12.0, 1.0, 1.0, 5.0, 3.0);
	if(sum < 0.008786091580986977 * factor)
		stage_sum += 0.523183286190033;
	else
		stage_sum += 0.23155799508094788;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 2.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(7.0, 2.0, 1.0, 6.0, 3.0);
	if(sum < 0.003671538084745407 * factor)
		stage_sum += 0.520425021648407;
	else
		stage_sum += 0.2977376878261566;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 14.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(14.0, 14.0, 3.0, 5.0, 2.0);
	if(sum < -0.0353364497423172 * factor)
		stage_sum += 0.7238878011703491;
	else
		stage_sum += 0.48615050315856934;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 8.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 9.0, 2.0, 1.0, 2.0);
	if(sum < -0.0006918924045749009 * factor)
		stage_sum += 0.31050220131874084;
	else
		stage_sum += 0.5229824781417847;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 7.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 8.0, 1.0, 1.0, 3.0);
	if(sum < -0.003394610946998 * factor)
		stage_sum += 0.3138968050479889;
	else
		stage_sum += 0.5210173726081848;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 6.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(7.0, 7.0, 1.0, 1.0, 2.0);
	if(sum < 0.0009856928372755647 * factor)
		stage_sum += 0.45365801453590393;
	else
		stage_sum += 0.6585097908973694;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 11.0, 18.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 11.0, 9.0, 2.0, 2.0);
	sum += rect_sum_ii(2.0, 13.0, 9.0, 2.0, 2.0);
	if(sum < -0.05016310140490532 * factor)
		stage_sum += 0.18044540286064148;
	else
		stage_sum += 0.5198916792869568;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 6.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(7.0, 7.0, 1.0, 1.0, 2.0);
	if(sum < -0.0022367259953171015 * factor)
		stage_sum += 0.7255702018737793;
	else
		stage_sum += 0.4651359021663666;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 15.0, 20.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 16.0, 20.0, 1.0, 2.0);
	if(sum < 0.0007432628772221506 * factor)
		stage_sum += 0.4412921071052551;
	else
		stage_sum += 0.5898545980453491;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 14.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 15.0, 2.0, 1.0, 3.0);
	if(sum < -0.0009348518215119839 * factor)
		stage_sum += 0.35000529885292053;
	else
		stage_sum += 0.5366017818450928;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 4.0, 1.0, 3.0);
	if(sum < 0.017497939988970757 * factor)
		stage_sum += 0.49121949076652527;
	else
		stage_sum += 0.8315284848213196;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 7.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 8.0, 2.0, 1.0, 3.0);
	if(sum < -0.0015200000489130616 * factor)
		stage_sum += 0.3570275902748108;
	else
		stage_sum += 0.537056028842926;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 10.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 11.0, 2.0, 1.0, 3.0);
	if(sum < 0.0007800394087098539 * factor)
		stage_sum += 0.43537721037864685;
	else
		stage_sum += 0.5967335104942322;


	if(stage_sum > 39.1072883605957)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage11(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 10.0, 4.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 10.0, 2.0, 2.0);
	if(sum < -0.00999455526471138 * factor)
		stage_sum += 0.6162583231925964;
	else
		stage_sum += 0.3054533004760742;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 7.0, 3.0, 2.0, 2.0);
	sum += rect_sum_ii(9.0, 9.0, 3.0, 2.0, 2.0);
	if(sum < -0.001108522992581129 * factor)
		stage_sum += 0.5818294882774353;
	else
		stage_sum += 0.3155578076839447;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(4.0, 9.0, 3.0, 2.0, 3.0);
	if(sum < 0.001036438043229282 * factor)
		stage_sum += 0.2552052140235901;
	else
		stage_sum += 0.5692911744117737;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 15.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 15.0, 2.0, 2.0, 2.0);
	sum += rect_sum_ii(11.0, 17.0, 2.0, 2.0, 2.0);
	if(sum < 0.000682113110087812 * factor)
		stage_sum += 0.3685089945793152;
	else
		stage_sum += 0.5934931039810181;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 9.0, 4.0, 1.0, 2.0);
	if(sum < -0.0006805734010413289 * factor)
		stage_sum += 0.23323920369148254;
	else
		stage_sum += 0.5474792122840881;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 1.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 1.0, 2.0, 3.0, 2.0);
	if(sum < 0.0002606878988444805 * factor)
		stage_sum += 0.32574570178985596;
	else
		stage_sum += 0.5667545795440674;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 15.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(5.0, 15.0, 2.0, 2.0, 2.0);
	sum += rect_sum_ii(7.0, 17.0, 2.0, 2.0, 2.0);
	if(sum < 0.0005160737200640142 * factor)
		stage_sum += 0.3744716942310333;
	else
		stage_sum += 0.5845472812652588;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 4.0, 7.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 2.0, 7.0, 2.0);
	if(sum < 0.0008500752155669034 * factor)
		stage_sum += 0.3420371115207672;
	else
		stage_sum += 0.5522807240486145;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 4.0, 3.0, 2.0);
	if(sum < -0.0018607829697430134 * factor)
		stage_sum += 0.2804419994354248;
	else
		stage_sum += 0.5375424027442932;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 9.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 10.0, 2.0, 1.0, 2.0);
	if(sum < -0.001503397012129426 * factor)
		stage_sum += 0.25790509581565857;
	else
		stage_sum += 0.5498952269554138;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 15.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 16.0, 5.0, 1.0, 3.0);
	if(sum < 0.0023478909861296415 * factor)
		stage_sum += 0.4175156056880951;
	else
		stage_sum += 0.6313710808753967;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 10.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 10.0, 2.0, 3.0, 2.0);
	if(sum < -0.00028880240279249847 * factor)
		stage_sum += 0.5865169763565063;
	else
		stage_sum += 0.4052666127681732;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 9.0, 8.0, 10.0, -1.0);
	sum += rect_sum_ii(6.0, 14.0, 8.0, 5.0, 2.0);
	if(sum < 0.008940547704696655 * factor)
		stage_sum += 0.5211141109466553;
	else
		stage_sum += 0.23186540603637695;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 11.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 11.0, 3.0, 2.0, 2.0);
	if(sum < -0.019327739253640175 * factor)
		stage_sum += 0.27534329891204834;
	else
		stage_sum += 0.5241525769233704;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 11.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 11.0, 3.0, 2.0, 2.0);
	if(sum < -0.0002020206011366099 * factor)
		stage_sum += 0.5722978711128235;
	else
		stage_sum += 0.3677195906639099;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 3.0, 8.0, 1.0, -1.0);
	sum += rect_sum_ii(11.0, 3.0, 4.0, 1.0, 2.0);
	if(sum < 0.002117906929925084 * factor)
		stage_sum += 0.44661080837249756;
	else
		stage_sum += 0.5542430877685547;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 3.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 3.0, 1.0, 2.0, 3.0);
	if(sum < -0.0017743760254234076 * factor)
		stage_sum += 0.2813253104686737;
	else
		stage_sum += 0.5300959944725037;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 5.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(14.0, 5.0, 3.0, 5.0, 2.0);
	if(sum < 0.004223445896059275 * factor)
		stage_sum += 0.439970999956131;
	else
		stage_sum += 0.5795428156852722;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 5.0, 2.0, 12.0, -1.0);
	sum += rect_sum_ii(7.0, 11.0, 2.0, 6.0, 2.0);
	if(sum < -0.01437522005289793 * factor)
		stage_sum += 0.29811179637908936;
	else
		stage_sum += 0.5292059183120728;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 11.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 12.0, 4.0, 1.0, 3.0);
	if(sum < -0.015349180437624454 * factor)
		stage_sum += 0.7705215215682983;
	else
		stage_sum += 0.4748171865940094;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 1.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 1.0, 1.0, 3.0, 2.0);
	if(sum < 0.000015152279956964776 * factor)
		stage_sum += 0.37188440561294556;
	else
		stage_sum += 0.5576897263526917;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 3.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(18.0, 5.0, 2.0, 2.0, 3.0);
	if(sum < -0.009129391983151436 * factor)
		stage_sum += 0.36151960492134094;
	else
		stage_sum += 0.5286766886711121;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 3.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 5.0, 2.0, 2.0, 3.0);
	if(sum < 0.0022512159775942564 * factor)
		stage_sum += 0.5364704728126526;
	else
		stage_sum += 0.34862980246543884;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 12.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 13.0, 2.0, 1.0, 3.0);
	if(sum < -0.0049696918576955795 * factor)
		stage_sum += 0.6927651762962341;
	else
		stage_sum += 0.4676836133003235;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 13.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 14.0, 4.0, 1.0, 3.0);
	if(sum < -0.012829010374844074 * factor)
		stage_sum += 0.7712153792381287;
	else
		stage_sum += 0.46607351303100586;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 0.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(18.0, 2.0, 2.0, 2.0, 3.0);
	if(sum < -0.009366006590425968 * factor)
		stage_sum += 0.33749839663505554;
	else
		stage_sum += 0.5351287722587585;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 2.0, 2.0, 2.0, 3.0);
	if(sum < 0.0032452319283038378 * factor)
		stage_sum += 0.5325189828872681;
	else
		stage_sum += 0.32896101474761963;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 6.0, 1.0, 3.0);
	if(sum < -0.011723560281097889 * factor)
		stage_sum += 0.6837652921676636;
	else
		stage_sum += 0.4754300117492676;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 4.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 4.0, 1.0, 4.0, 2.0);
	if(sum < 0.00002925794069597032 * factor)
		stage_sum += 0.357208788394928;
	else
		stage_sum += 0.5360502004623413;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 5.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 4.0, 2.0, 3.0);
	if(sum < -0.000022244219508138485 * factor)
		stage_sum += 0.5541427135467529;
	else
		stage_sum += 0.3552064001560211;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 4.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 4.0, 1.0, 2.0, 2.0);
	if(sum < 0.005088150966912508 * factor)
		stage_sum += 0.5070844292640686;
	else
		stage_sum += 0.1256462037563324;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 14.0, 14.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 14.0, 7.0, 2.0, 2.0);
	sum += rect_sum_ii(3.0, 16.0, 7.0, 2.0, 2.0);
	if(sum < 0.027429679408669472 * factor)
		stage_sum += 0.5269560217857361;
	else
		stage_sum += 0.16258180141448975;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 15.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 15.0, 3.0, 1.0, 2.0);
	sum += rect_sum_ii(9.0, 16.0, 3.0, 1.0, 2.0);
	if(sum < -0.00641428679227829 * factor)
		stage_sum += 0.7145588994026184;
	else
		stage_sum += 0.45841971039772034;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 15.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(14.0, 16.0, 6.0, 1.0, 2.0);
	if(sum < 0.003347995923832059 * factor)
		stage_sum += 0.5398612022399902;
	else
		stage_sum += 0.34946969151496887;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 12.0, 12.0, 8.0, -1.0);
	sum += rect_sum_ii(2.0, 16.0, 12.0, 4.0, 2.0);
	if(sum < -0.08263549208641052 * factor)
		stage_sum += 0.24391929805278778;
	else
		stage_sum += 0.5160226225852966;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 7.0, 7.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 8.0, 7.0, 1.0, 2.0);
	if(sum < 0.0010261740535497665 * factor)
		stage_sum += 0.38868919014930725;
	else
		stage_sum += 0.5767908096313477;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 18.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 3.0, 18.0, 1.0, 2.0);
	if(sum < -0.0016307090409100056 * factor)
		stage_sum += 0.33894580602645874;
	else
		stage_sum += 0.5347700715065002;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 6.0, 2.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 1.0, 5.0, 2.0);
	if(sum < 0.0024546680506318808 * factor)
		stage_sum += 0.4601413905620575;
	else
		stage_sum += 0.638724684715271;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 5.0, 3.0, 8.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 1.0, 8.0, 3.0);
	if(sum < -0.0009947651997208595 * factor)
		stage_sum += 0.5769879221916199;
	else
		stage_sum += 0.4120396077632904;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 6.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 1.0, 4.0, 3.0);
	if(sum < 0.015409190207719803 * factor)
		stage_sum += 0.4878709018230438;
	else
		stage_sum += 0.7089822292327881;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 13.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(4.0, 14.0, 3.0, 1.0, 2.0);
	if(sum < 0.001178440055809915 * factor)
		stage_sum += 0.5263553261756897;
	else
		stage_sum += 0.28952449560165405;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 4.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 4.0, 2.0, 3.0, 3.0);
	if(sum < -0.02770191989839077 * factor)
		stage_sum += 0.14988289773464203;
	else
		stage_sum += 0.5219606757164001;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 4.0, 2.0, 3.0, 3.0);
	if(sum < -0.029505399987101555 * factor)
		stage_sum += 0.024893319234251976;
	else
		stage_sum += 0.4999816119670868;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 11.0, 5.0, 2.0, -1.0);
	sum += rect_sum_ii(14.0, 12.0, 5.0, 1.0, 2.0);
	if(sum < 0.0004515943001024425 * factor)
		stage_sum += 0.5464622974395752;
	else
		stage_sum += 0.40296629071235657;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 2.0, 6.0, 9.0, -1.0);
	sum += rect_sum_ii(3.0, 2.0, 2.0, 9.0, 3.0);
	if(sum < 0.007177263963967562 * factor)
		stage_sum += 0.42710569500923157;
	else
		stage_sum += 0.5866296887397766;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 6.0, 6.0, 13.0, -1.0);
	sum += rect_sum_ii(14.0, 6.0, 3.0, 13.0, 2.0);
	if(sum < -0.07418204843997955 * factor)
		stage_sum += 0.6874179244041443;
	else
		stage_sum += 0.49190279841423035;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 6.0, 14.0, 8.0, -1.0);
	sum += rect_sum_ii(3.0, 6.0, 7.0, 4.0, 2.0);
	sum += rect_sum_ii(10.0, 10.0, 7.0, 4.0, 2.0);
	if(sum < -0.017254160717129707 * factor)
		stage_sum += 0.3370676040649414;
	else
		stage_sum += 0.534873902797699;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 0.0, 4.0, 11.0, -1.0);
	sum += rect_sum_ii(16.0, 0.0, 2.0, 11.0, 2.0);
	if(sum < 0.01485155988484621 * factor)
		stage_sum += 0.46267929673194885;
	else
		stage_sum += 0.6129904985427856;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 4.0, 12.0, 12.0, -1.0);
	sum += rect_sum_ii(3.0, 4.0, 6.0, 6.0, 2.0);
	sum += rect_sum_ii(9.0, 10.0, 6.0, 6.0, 2.0);
	if(sum < 0.010002000257372856 * factor)
		stage_sum += 0.5346122980117798;
	else
		stage_sum += 0.34234538674354553;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 4.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 5.0, 5.0, 1.0, 3.0);
	if(sum < 0.0020138120744377375 * factor)
		stage_sum += 0.46438300609588623;
	else
		stage_sum += 0.5824304223060608;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 11.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(4.0, 12.0, 4.0, 1.0, 2.0);
	if(sum < 0.0015135470312088728 * factor)
		stage_sum += 0.5196396112442017;
	else
		stage_sum += 0.2856149971485138;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 7.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 2.0, 2.0);
	if(sum < 0.003138143103569746 * factor)
		stage_sum += 0.4838162958621979;
	else
		stage_sum += 0.5958529710769653;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 7.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 1.0, 2.0, 2.0);
	if(sum < -0.005145044066011906 * factor)
		stage_sum += 0.8920302987098694;
	else
		stage_sum += 0.4741412103176117;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 17.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 17.0, 1.0, 2.0, 3.0);
	if(sum < -0.004473670851439238 * factor)
		stage_sum += 0.20339429378509521;
	else
		stage_sum += 0.5337278842926025;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 7.0, 3.0, 1.0, 3.0);
	if(sum < 0.001962847076356411 * factor)
		stage_sum += 0.45716339349746704;
	else
		stage_sum += 0.6725863218307495;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 0.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 0.0, 1.0, 3.0, 3.0);
	if(sum < 0.005426045041531324 * factor)
		stage_sum += 0.5271108150482178;
	else
		stage_sum += 0.28456708788871765;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 3.0, 1.0, 2.0);
	sum += rect_sum_ii(8.0, 7.0, 3.0, 1.0, 2.0);
	if(sum < 0.0004961146041750908 * factor)
		stage_sum += 0.41383129358291626;
	else
		stage_sum += 0.5718597769737244;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 16.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 17.0, 4.0, 1.0, 3.0);
	if(sum < 0.009372878819704056 * factor)
		stage_sum += 0.5225151181221008;
	else
		stage_sum += 0.28048470616340637;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 12.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(3.0, 13.0, 3.0, 1.0, 2.0);
	if(sum < 0.0006050089723430574 * factor)
		stage_sum += 0.523676872253418;
	else
		stage_sum += 0.3314523994922638;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 12.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 13.0, 3.0, 1.0, 2.0);
	if(sum < 0.0005679255118593574 * factor)
		stage_sum += 0.45310598611831665;
	else
		stage_sum += 0.6276971101760864;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 11.0, 16.0, 4.0, -1.0);
	sum += rect_sum_ii(1.0, 11.0, 8.0, 2.0, 2.0);
	sum += rect_sum_ii(9.0, 13.0, 8.0, 2.0, 2.0);
	if(sum < 0.024644339457154274 * factor)
		stage_sum += 0.5130851864814758;
	else
		stage_sum += 0.2017143964767456;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 4.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 5.0, 3.0, 1.0, 3.0);
	if(sum < -0.010290450416505337 * factor)
		stage_sum += 0.7786595225334167;
	else
		stage_sum += 0.4876641035079956;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 5.0, 5.0, 1.0, 3.0);
	if(sum < 0.002062941901385784 * factor)
		stage_sum += 0.4288598895072937;
	else
		stage_sum += 0.5881264209747314;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 16.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 17.0, 4.0, 1.0, 3.0);
	if(sum < -0.005051948130130768 * factor)
		stage_sum += 0.3523977994918823;
	else
		stage_sum += 0.5286008715629578;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 5.0, 3.0, 1.0, 3.0);
	if(sum < -0.0057692620903253555 * factor)
		stage_sum += 0.6841086149215698;
	else
		stage_sum += 0.45880940556526184;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 0.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 1.0, 2.0, 1.0, 2.0);
	if(sum < -0.0004578994121402502 * factor)
		stage_sum += 0.35655200481414795;
	else
		stage_sum += 0.5485978126525879;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 9.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 10.0, 4.0, 1.0, 2.0);
	if(sum < -0.0007591883768327534 * factor)
		stage_sum += 0.33687931299209595;
	else
		stage_sum += 0.5254197120666504;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 8.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 9.0, 4.0, 1.0, 3.0);
	if(sum < -0.001773725962266326 * factor)
		stage_sum += 0.3422161042690277;
	else
		stage_sum += 0.5454015135765076;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 13.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(2.0, 13.0, 2.0, 3.0, 3.0);
	if(sum < -0.008561046794056892 * factor)
		stage_sum += 0.6533612012863159;
	else
		stage_sum += 0.4485856890678406;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 14.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 15.0, 3.0, 1.0, 2.0);
	if(sum < 0.0017277270089834929 * factor)
		stage_sum += 0.5307580232620239;
	else
		stage_sum += 0.3925352990627289;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 18.0, 18.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 18.0, 6.0, 2.0, 3.0);
	if(sum < -0.028199609369039536 * factor)
		stage_sum += 0.685745894908905;
	else
		stage_sum += 0.4588584005832672;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 14.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 15.0, 3.0, 1.0, 2.0);
	if(sum < -0.001778110978193581 * factor)
		stage_sum += 0.4037851095199585;
	else
		stage_sum += 0.5369856953620911;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 14.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(1.0, 15.0, 3.0, 1.0, 2.0);
	if(sum < 0.00033177141449414194 * factor)
		stage_sum += 0.539979875087738;
	else
		stage_sum += 0.3705750107765198;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 14.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 15.0, 6.0, 1.0, 3.0);
	if(sum < 0.0026385399978607893 * factor)
		stage_sum += 0.46654370427131653;
	else
		stage_sum += 0.6452730894088745;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 14.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 15.0, 8.0, 1.0, 3.0);
	if(sum < -0.0021183069329708815 * factor)
		stage_sum += 0.5914781093597412;
	else
		stage_sum += 0.4064677059650421;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 6.0, 4.0, 14.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 2.0, 14.0, 2.0);
	if(sum < -0.014773289673030376 * factor)
		stage_sum += 0.3642038106918335;
	else
		stage_sum += 0.5294762849807739;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 4.0, 14.0, -1.0);
	sum += rect_sum_ii(8.0, 6.0, 2.0, 14.0, 2.0);
	if(sum < -0.016815440729260445 * factor)
		stage_sum += 0.26642319560050964;
	else
		stage_sum += 0.5144972801208496;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 5.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 6.0, 2.0, 1.0, 3.0);
	if(sum < -0.006337014026939869 * factor)
		stage_sum += 0.6779531240463257;
	else
		stage_sum += 0.48520979285240173;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 16.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 16.0, 2.0, 1.0, 3.0);
	if(sum < -0.000044560048991115764 * factor)
		stage_sum += 0.5613964796066284;
	else
		stage_sum += 0.41530540585517883;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 12.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 13.0, 3.0, 1.0, 3.0);
	if(sum < -0.0010240620467811823 * factor)
		stage_sum += 0.5964478254318237;
	else
		stage_sum += 0.4566304087638855;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 0.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 0.0, 1.0, 3.0, 3.0);
	if(sum < -0.00231616897508502 * factor)
		stage_sum += 0.2976115047931671;
	else
		stage_sum += 0.5188159942626953;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 0.0, 16.0, 18.0, -1.0);
	sum += rect_sum_ii(4.0, 9.0, 16.0, 9.0, 2.0);
	if(sum < 0.5321757197380066 * factor)
		stage_sum += 0.5187839269638062;
	else
		stage_sum += 0.22026319801807404;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 1.0, 16.0, 14.0, -1.0);
	sum += rect_sum_ii(1.0, 8.0, 16.0, 7.0, 2.0);
	if(sum < -0.1664305031299591 * factor)
		stage_sum += 0.18660229444503784;
	else
		stage_sum += 0.5060343146324158;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 9.0, 15.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 9.0, 5.0, 4.0, 3.0);
	if(sum < 0.11253529787063599 * factor)
		stage_sum += 0.5212125182151794;
	else
		stage_sum += 0.11850229650735855;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 12.0, 7.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 13.0, 7.0, 1.0, 3.0);
	if(sum < 0.009304686449468136 * factor)
		stage_sum += 0.45899370312690735;
	else
		stage_sum += 0.6826149225234985;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 15.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(14.0, 16.0, 2.0, 1.0, 3.0);
	if(sum < -0.004625509958714247 * factor)
		stage_sum += 0.3079940974712372;
	else
		stage_sum += 0.5225008726119995;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 3.0, 16.0, 14.0, -1.0);
	sum += rect_sum_ii(2.0, 3.0, 8.0, 7.0, 2.0);
	sum += rect_sum_ii(10.0, 10.0, 8.0, 7.0, 2.0);
	if(sum < -0.11116469651460648 * factor)
		stage_sum += 0.21010440587997437;
	else
		stage_sum += 0.5080801844596863;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 2.0, 4.0, 18.0, -1.0);
	sum += rect_sum_ii(18.0, 2.0, 2.0, 9.0, 2.0);
	sum += rect_sum_ii(16.0, 11.0, 2.0, 9.0, 2.0);
	if(sum < -0.010888439603149891 * factor)
		stage_sum += 0.5765355229377747;
	else
		stage_sum += 0.47904640436172485;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 15.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 16.0, 2.0, 1.0, 3.0);
	if(sum < 0.005856430158019066 * factor)
		stage_sum += 0.5065100193023682;
	else
		stage_sum += 0.15635989606380463;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 2.0, 4.0, 18.0, -1.0);
	sum += rect_sum_ii(18.0, 2.0, 2.0, 9.0, 2.0);
	sum += rect_sum_ii(16.0, 11.0, 2.0, 9.0, 2.0);
	if(sum < 0.054854389280080795 * factor)
		stage_sum += 0.49669149518013;
	else
		stage_sum += 0.7230510711669922;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 1.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 2.0, 8.0, 1.0, 3.0);
	if(sum < -0.011197339743375778 * factor)
		stage_sum += 0.2194979041814804;
	else
		stage_sum += 0.5098798274993896;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 11.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 12.0, 4.0, 1.0, 3.0);
	if(sum < 0.004406907130032778 * factor)
		stage_sum += 0.4778401851654053;
	else
		stage_sum += 0.6770902872085571;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 11.0, 5.0, 9.0, -1.0);
	sum += rect_sum_ii(5.0, 14.0, 5.0, 3.0, 3.0);
	if(sum < -0.06366529315710068 * factor)
		stage_sum += 0.19363629817962646;
	else
		stage_sum += 0.5081024169921875;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 0.0, 4.0, 11.0, -1.0);
	sum += rect_sum_ii(16.0, 0.0, 2.0, 11.0, 2.0);
	if(sum < -0.009808149188756943 * factor)
		stage_sum += 0.599906325340271;
	else
		stage_sum += 0.4810341000556946;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 0.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 0.0, 2.0, 1.0, 3.0);
	if(sum < -0.0021717099007219076 * factor)
		stage_sum += 0.33383339643478394;
	else
		stage_sum += 0.5235472917556763;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 3.0, 3.0, 7.0, -1.0);
	sum += rect_sum_ii(17.0, 3.0, 1.0, 7.0, 3.0);
	if(sum < -0.013315520249307156 * factor)
		stage_sum += 0.6617069840431213;
	else
		stage_sum += 0.4919213056564331;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 3.0, 3.0, 7.0, -1.0);
	sum += rect_sum_ii(2.0, 3.0, 1.0, 7.0, 3.0);
	if(sum < 0.002544207964092493 * factor)
		stage_sum += 0.44887441396713257;
	else
		stage_sum += 0.6082184910774231;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 6.0, 12.0, -1.0);
	sum += rect_sum_ii(7.0, 12.0, 6.0, 4.0, 3.0);
	if(sum < 0.012037839740514755 * factor)
		stage_sum += 0.540939211845398;
	else
		stage_sum += 0.3292432129383087;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 4.0, 11.0, -1.0);
	sum += rect_sum_ii(2.0, 0.0, 2.0, 11.0, 2.0);
	if(sum < -0.020701050758361816 * factor)
		stage_sum += 0.6819120049476624;
	else
		stage_sum += 0.4594995975494385;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 0.0, 6.0, 20.0, -1.0);
	sum += rect_sum_ii(14.0, 0.0, 3.0, 20.0, 2.0);
	if(sum < 0.027608279138803482 * factor)
		stage_sum += 0.46307921409606934;
	else
		stage_sum += 0.5767282843589783;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 3.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 4.0, 1.0, 1.0, 2.0);
	if(sum < 0.0012370620388537645 * factor)
		stage_sum += 0.5165379047393799;
	else
		stage_sum += 0.2635016143321991;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 10.0, 8.0, -1.0);
	sum += rect_sum_ii(10.0, 5.0, 5.0, 4.0, 2.0);
	sum += rect_sum_ii(5.0, 9.0, 5.0, 4.0, 2.0);
	if(sum < -0.037669338285923004 * factor)
		stage_sum += 0.2536393105983734;
	else
		stage_sum += 0.5278980135917664;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 7.0, 12.0, 4.0, -1.0);
	sum += rect_sum_ii(4.0, 7.0, 6.0, 2.0, 2.0);
	sum += rect_sum_ii(10.0, 9.0, 6.0, 2.0, 2.0);
	if(sum < -0.0018057259730994701 * factor)
		stage_sum += 0.39851561188697815;
	else
		stage_sum += 0.5517500042915344;


	if(stage_sum > 50.61048126220703)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage12(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 1.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(5.0, 1.0, 3.0, 4.0, 2.0);
	if(sum < 0.004429902881383896 * factor)
		stage_sum += 0.28910180926322937;
	else
		stage_sum += 0.633522629737854;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 7.0, 3.0, 2.0, 2.0);
	sum += rect_sum_ii(9.0, 9.0, 3.0, 2.0, 2.0);
	if(sum < -0.0023813319858163595 * factor)
		stage_sum += 0.621178925037384;
	else
		stage_sum += 0.3477487862110138;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 9.0, 2.0, 3.0, 2.0);
	if(sum < 0.0022915711160749197 * factor)
		stage_sum += 0.22544120252132416;
	else
		stage_sum += 0.5582118034362793;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 16.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 16.0, 3.0, 2.0, 2.0);
	sum += rect_sum_ii(9.0, 18.0, 3.0, 2.0, 2.0);
	if(sum < 0.0009945794008672237 * factor)
		stage_sum += 0.37117108702659607;
	else
		stage_sum += 0.5930070877075195;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 4.0, 2.0, 12.0, -1.0);
	sum += rect_sum_ii(9.0, 10.0, 2.0, 6.0, 2.0);
	if(sum < 0.0007716466789133847 * factor)
		stage_sum += 0.565172016620636;
	else
		stage_sum += 0.334799587726593;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 1.0, 6.0, 18.0, -1.0);
	sum += rect_sum_ii(9.0, 1.0, 2.0, 18.0, 3.0);
	if(sum < -0.001138641033321619 * factor)
		stage_sum += 0.3069126009941101;
	else
		stage_sum += 0.5508630871772766;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 12.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 12.0, 4.0, 2.0, 3.0);
	if(sum < -0.0001640303962631151 * factor)
		stage_sum += 0.576282799243927;
	else
		stage_sum += 0.3699047863483429;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 8.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 9.0, 6.0, 1.0, 2.0);
	if(sum < 0.000029793529392918572 * factor)
		stage_sum += 0.2644244134426117;
	else
		stage_sum += 0.5437911152839661;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 0.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 0.0, 1.0, 6.0, 3.0);
	if(sum < 0.008577490225434303 * factor)
		stage_sum += 0.5051138997077942;
	else
		stage_sum += 0.17957249283790588;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 18.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 19.0, 3.0, 1.0, 2.0);
	if(sum < -0.0002603268949314952 * factor)
		stage_sum += 0.5826969146728516;
	else
		stage_sum += 0.44468268752098083;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 1.0, 17.0, 4.0, -1.0);
	sum += rect_sum_ii(1.0, 3.0, 17.0, 2.0, 2.0);
	if(sum < -0.006140463054180145 * factor)
		stage_sum += 0.31138521432876587;
	else
		stage_sum += 0.5346971750259399;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 8.0, 4.0, 12.0, -1.0);
	sum += rect_sum_ii(11.0, 8.0, 2.0, 12.0, 2.0);
	if(sum < -0.023086950182914734 * factor)
		stage_sum += 0.32779461145401;
	else
		stage_sum += 0.533119797706604;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 4.0, 1.0, 3.0);
	if(sum < -0.014243650250136852 * factor)
		stage_sum += 0.7381709814071655;
	else
		stage_sum += 0.4588063061237335;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 3.0, 2.0, 17.0, -1.0);
	sum += rect_sum_ii(12.0, 3.0, 1.0, 17.0, 2.0);
	if(sum < 0.019487129524350166 * factor)
		stage_sum += 0.5256630778312683;
	else
		stage_sum += 0.22744719684123993;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 7.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(6.0, 7.0, 2.0, 1.0, 3.0);
	if(sum < -0.0009668110869824886 * factor)
		stage_sum += 0.5511230826377869;
	else
		stage_sum += 0.3815006911754608;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 3.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(18.0, 4.0, 2.0, 1.0, 3.0);
	if(sum < 0.003147470997646451 * factor)
		stage_sum += 0.5425636768341064;
	else
		stage_sum += 0.2543726861476898;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 4.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 6.0, 3.0, 2.0, 2.0);
	if(sum < -0.00018026070029009134 * factor)
		stage_sum += 0.5380191802978516;
	else
		stage_sum += 0.3406304121017456;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 5.0, 12.0, 10.0, -1.0);
	sum += rect_sum_ii(4.0, 10.0, 12.0, 5.0, 2.0);
	if(sum < -0.006026626098901033 * factor)
		stage_sum += 0.3035801947116852;
	else
		stage_sum += 0.54205721616745;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 18.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 18.0, 2.0, 2.0, 2.0);
	if(sum < 0.00044462960795499384 * factor)
		stage_sum += 0.3990997076034546;
	else
		stage_sum += 0.5660110116004944;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 2.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(17.0, 4.0, 3.0, 2.0, 3.0);
	if(sum < 0.002260976005345583 * factor)
		stage_sum += 0.5562806725502014;
	else
		stage_sum += 0.39406880736351013;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 7.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 2.0, 6.0, 3.0);
	if(sum < 0.051133058965206146 * factor)
		stage_sum += 0.4609653949737549;
	else
		stage_sum += 0.7118561863899231;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 2.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(17.0, 4.0, 3.0, 2.0, 3.0);
	if(sum < -0.017786309123039246 * factor)
		stage_sum += 0.23161660134792328;
	else
		stage_sum += 0.5322144031524658;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 0.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 0.0, 1.0, 4.0, 3.0);
	if(sum < -0.004967962857335806 * factor)
		stage_sum += 0.23307719826698303;
	else
		stage_sum += 0.5122029185295105;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 14.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 15.0, 2.0, 1.0, 3.0);
	if(sum < 0.002066768938675523 * factor)
		stage_sum += 0.46574440598487854;
	else
		stage_sum += 0.6455488204956055;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 12.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 13.0, 6.0, 1.0, 3.0);
	if(sum < 0.007441376801580191 * factor)
		stage_sum += 0.5154392123222351;
	else
		stage_sum += 0.23616339266300201;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 4.0, 1.0, 3.0);
	if(sum < -0.003627727972343564 * factor)
		stage_sum += 0.6219773292541504;
	else
		stage_sum += 0.44766610860824585;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 12.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 13.0, 2.0, 1.0, 3.0);
	if(sum < -0.005353075917810202 * factor)
		stage_sum += 0.18373550474643707;
	else
		stage_sum += 0.5102208256721497;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 12.0, 7.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 4.0, 7.0, 3.0);
	if(sum < 0.1453091949224472 * factor)
		stage_sum += 0.5145987272262573;
	else
		stage_sum += 0.15359309315681458;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 4.0, 3.0, 2.0, 3.0);
	if(sum < 0.0024394490756094456 * factor)
		stage_sum += 0.5343660116195679;
	else
		stage_sum += 0.3624661862850189;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 6.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(14.0, 7.0, 1.0, 1.0, 3.0);
	if(sum < -0.003128339070826769 * factor)
		stage_sum += 0.6215007901191711;
	else
		stage_sum += 0.48455920815467834;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 0.0, 3.0, 14.0, -1.0);
	sum += rect_sum_ii(3.0, 0.0, 1.0, 14.0, 3.0);
	if(sum < 0.0017940260004252195 * factor)
		stage_sum += 0.42992618680000305;
	else
		stage_sum += 0.5824198126792908;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 14.0, 5.0, 6.0, -1.0);
	sum += rect_sum_ii(12.0, 16.0, 5.0, 2.0, 3.0);
	if(sum < 0.03625382110476494 * factor)
		stage_sum += 0.5260334014892578;
	else
		stage_sum += 0.1439467966556549;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 14.0, 5.0, 6.0, -1.0);
	sum += rect_sum_ii(4.0, 16.0, 5.0, 2.0, 3.0);
	if(sum < -0.005174672231078148 * factor)
		stage_sum += 0.35065388679504395;
	else
		stage_sum += 0.5287045240402222;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 10.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 10.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(11.0, 11.0, 1.0, 1.0, 2.0);
	if(sum < 0.0006538329762406647 * factor)
		stage_sum += 0.4809640944004059;
	else
		stage_sum += 0.6122040152549744;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 0.0, 3.0, 14.0, -1.0);
	sum += rect_sum_ii(6.0, 0.0, 1.0, 14.0, 3.0);
	if(sum < -0.026480229571461678 * factor)
		stage_sum += 0.11393620073795319;
	else
		stage_sum += 0.5045586228370667;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 15.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 16.0, 2.0, 1.0, 3.0);
	if(sum < -0.0030440660193562508 * factor)
		stage_sum += 0.6352095007896423;
	else
		stage_sum += 0.47947341203689575;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 3.0, 2.0, 1.0, 3.0);
	if(sum < 0.0036993520334362984 * factor)
		stage_sum += 0.5131118297576904;
	else
		stage_sum += 0.24985109269618988;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 11.0, 12.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 14.0, 12.0, 3.0, 2.0);
	if(sum < -0.0003676293126773089 * factor)
		stage_sum += 0.54213947057724;
	else
		stage_sum += 0.37095320224761963;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 11.0, 3.0, 9.0, -1.0);
	sum += rect_sum_ii(6.0, 14.0, 3.0, 3.0, 3.0);
	if(sum < -0.041382260620594025 * factor)
		stage_sum += 0.1894959956407547;
	else
		stage_sum += 0.5081691741943359;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 10.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 10.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(11.0, 11.0, 1.0, 1.0, 2.0);
	if(sum < -0.0010532729793339968 * factor)
		stage_sum += 0.645436704158783;
	else
		stage_sum += 0.4783608913421631;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 7.0, 1.0, 1.0, 3.0);
	if(sum < -0.0021648600231856108 * factor)
		stage_sum += 0.6215031147003174;
	else
		stage_sum += 0.449982613325119;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 9.0, 13.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 10.0, 13.0, 1.0, 3.0);
	if(sum < -0.0005674774874933064 * factor)
		stage_sum += 0.3712610900402069;
	else
		stage_sum += 0.5419334769248962;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 15.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 7.0, 5.0, 6.0, 3.0);
	if(sum < 0.173758402466774 * factor)
		stage_sum += 0.5023643970489502;
	else
		stage_sum += 0.12157420068979263;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 5.0, 12.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 4.0, 6.0, 3.0);
	if(sum < -0.0029049699660390615 * factor)
		stage_sum += 0.32402679324150085;
	else
		stage_sum += 0.5381883978843689;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 10.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 11.0, 4.0, 1.0, 3.0);
	if(sum < 0.0012299539521336555 * factor)
		stage_sum += 0.41655078530311584;
	else
		stage_sum += 0.5703486204147339;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 14.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 15.0, 1.0, 1.0, 3.0);
	if(sum < -0.0005432923790067434 * factor)
		stage_sum += 0.3854042887687683;
	else
		stage_sum += 0.554754912853241;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 11.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 12.0, 5.0, 1.0, 3.0);
	if(sum < -0.008329725824296474 * factor)
		stage_sum += 0.22044940292835236;
	else
		stage_sum += 0.5097082853317261;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 1.0, 7.0, 12.0, -1.0);
	sum += rect_sum_ii(7.0, 7.0, 7.0, 6.0, 2.0);
	if(sum < -0.00010417630255687982 * factor)
		stage_sum += 0.560706615447998;
	else
		stage_sum += 0.4303036034107208;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 1.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(0.0, 1.0, 3.0, 5.0, 2.0);
	sum += rect_sum_ii(3.0, 6.0, 3.0, 5.0, 2.0);
	if(sum < 0.031204700469970703 * factor)
		stage_sum += 0.4621657133102417;
	else
		stage_sum += 0.6982004046440125;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 1.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(16.0, 2.0, 4.0, 1.0, 3.0);
	if(sum < 0.007894350215792656 * factor)
		stage_sum += 0.5269594192504883;
	else
		stage_sum += 0.22690680623054504;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 2.0, 1.0, 3.0);
	if(sum < -0.004364531021565199 * factor)
		stage_sum += 0.6359223127365112;
	else
		stage_sum += 0.4537956118583679;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 2.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(13.0, 2.0, 1.0, 5.0, 3.0);
	if(sum < 0.007679305970668793 * factor)
		stage_sum += 0.5274767875671387;
	else
		stage_sum += 0.274048388004303;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 3.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 5.0, 4.0, 2.0, 3.0);
	if(sum < -0.025431139394640923 * factor)
		stage_sum += 0.20385199785232544;
	else
		stage_sum += 0.5071732997894287;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 13.0, 4.0, 1.0, 2.0);
	if(sum < 0.0008200060110539198 * factor)
		stage_sum += 0.4587455093860626;
	else
		stage_sum += 0.6119868159294128;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 18.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.002928460016846657 * factor)
		stage_sum += 0.5071274042129517;
	else
		stage_sum += 0.20282049477100372;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 10.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 10.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(11.0, 11.0, 1.0, 1.0, 2.0);
	if(sum < 0.00004525647091213614 * factor)
		stage_sum += 0.4812104105949402;
	else
		stage_sum += 0.5430821776390076;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 10.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 10.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(8.0, 11.0, 1.0, 1.0, 2.0);
	if(sum < 0.0013158309739083052 * factor)
		stage_sum += 0.4625813961029053;
	else
		stage_sum += 0.6779323220252991;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 11.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 13.0, 4.0, 2.0, 2.0);
	if(sum < 0.0015870389761403203 * factor)
		stage_sum += 0.5386291742324829;
	else
		stage_sum += 0.34314650297164917;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 3.0, 8.0, -1.0);
	sum += rect_sum_ii(9.0, 12.0, 1.0, 8.0, 3.0);
	if(sum < -0.021539660170674324 * factor)
		stage_sum += 0.025942500680685043;
	else
		stage_sum += 0.5003222823143005;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 0.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 1.0, 6.0, 1.0, 3.0);
	if(sum < 0.01433448027819395 * factor)
		stage_sum += 0.5202844738960266;
	else
		stage_sum += 0.15906329452991486;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 8.0, 1.0, 4.0, 3.0);
	if(sum < -0.008388138376176357 * factor)
		stage_sum += 0.728248119354248;
	else
		stage_sum += 0.46480441093444824;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 10.0, 10.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 5.0, 5.0, 2.0);
	sum += rect_sum_ii(5.0, 12.0, 5.0, 5.0, 2.0);
	if(sum < 0.00919068418443203 * factor)
		stage_sum += 0.556235671043396;
	else
		stage_sum += 0.39231911301612854;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 18.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(3.0, 18.0, 4.0, 1.0, 2.0);
	sum += rect_sum_ii(7.0, 19.0, 4.0, 1.0, 2.0);
	if(sum < -0.005845305975526571 * factor)
		stage_sum += 0.6803392767906189;
	else
		stage_sum += 0.46291279792785645;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 2.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(12.0, 2.0, 2.0, 8.0, 3.0);
	if(sum < -0.05470779910683632 * factor)
		stage_sum += 0.25616711378097534;
	else
		stage_sum += 0.5206125974655151;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 2.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(6.0, 2.0, 2.0, 8.0, 3.0);
	if(sum < 0.009114277549088001 * factor)
		stage_sum += 0.518962025642395;
	else
		stage_sum += 0.3053877055644989;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 0.0, 3.0, 7.0, -1.0);
	sum += rect_sum_ii(12.0, 0.0, 1.0, 7.0, 3.0);
	if(sum < -0.015575000084936619 * factor)
		stage_sum += 0.12950749695301056;
	else
		stage_sum += 0.5169094800949097;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 11.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(8.0, 11.0, 1.0, 1.0, 2.0);
	if(sum < -0.0001205060034408234 * factor)
		stage_sum += 0.5735098123550415;
	else
		stage_sum += 0.42308250069618225;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 14.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 15.0, 1.0, 1.0, 3.0);
	if(sum < 0.0012273970060050488 * factor)
		stage_sum += 0.5289878249168396;
	else
		stage_sum += 0.40797919034957886;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 15.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 15.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(8.0, 16.0, 1.0, 1.0, 2.0);
	if(sum < -0.0012186600361019373 * factor)
		stage_sum += 0.6575639843940735;
	else
		stage_sum += 0.45744091272354126;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 14.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 15.0, 1.0, 1.0, 3.0);
	if(sum < -0.0033256649039685726 * factor)
		stage_sum += 0.36280471086502075;
	else
		stage_sum += 0.5195019841194153;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 3.0, 7.0, -1.0);
	sum += rect_sum_ii(7.0, 0.0, 1.0, 7.0, 3.0);
	if(sum < -0.013288309797644615 * factor)
		stage_sum += 0.12842659652233124;
	else
		stage_sum += 0.504348874092102;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 1.0, 2.0, 7.0, -1.0);
	sum += rect_sum_ii(18.0, 1.0, 1.0, 7.0, 2.0);
	if(sum < -0.0033839771058410406 * factor)
		stage_sum += 0.6292240023612976;
	else
		stage_sum += 0.475750595331192;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 0.0, 8.0, 20.0, -1.0);
	sum += rect_sum_ii(2.0, 10.0, 8.0, 10.0, 2.0);
	if(sum < -0.21954220533370972 * factor)
		stage_sum += 0.148773193359375;
	else
		stage_sum += 0.5065013766288757;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 0.0, 15.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 2.0, 15.0, 2.0, 3.0);
	if(sum < 0.004911170806735754 * factor)
		stage_sum += 0.425610214471817;
	else
		stage_sum += 0.5665838718414307;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 3.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(4.0, 4.0, 12.0, 1.0, 2.0);
	if(sum < -0.00018744950648397207 * factor)
		stage_sum += 0.4004144072532654;
	else
		stage_sum += 0.5586857199668884;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 0.0, 4.0, 5.0, -1.0);
	sum += rect_sum_ii(16.0, 0.0, 2.0, 5.0, 2.0);
	if(sum < -0.00521786417812109 * factor)
		stage_sum += 0.6009116172790527;
	else
		stage_sum += 0.48127061128616333;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 0.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 0.0, 1.0, 4.0, 3.0);
	if(sum < -0.0011111519997939467 * factor)
		stage_sum += 0.35149338841438293;
	else
		stage_sum += 0.5287089943885803;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 0.0, 4.0, 5.0, -1.0);
	sum += rect_sum_ii(16.0, 0.0, 2.0, 5.0, 2.0);
	if(sum < 0.004403640050441027 * factor)
		stage_sum += 0.4642275869846344;
	else
		stage_sum += 0.5924085974693298;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 6.0, 13.0, -1.0);
	sum += rect_sum_ii(3.0, 7.0, 2.0, 13.0, 3.0);
	if(sum < 0.12299499660730362 * factor)
		stage_sum += 0.5025529265403748;
	else
		stage_sum += 0.06915248185396194;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 0.0, 4.0, 5.0, -1.0);
	sum += rect_sum_ii(16.0, 0.0, 2.0, 5.0, 2.0);
	if(sum < -0.012313510291278362 * factor)
		stage_sum += 0.5884591937065125;
	else
		stage_sum += 0.49340128898620605;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 4.0, 5.0, -1.0);
	sum += rect_sum_ii(2.0, 0.0, 2.0, 5.0, 2.0);
	if(sum < 0.004147103987634182 * factor)
		stage_sum += 0.4372239112854004;
	else
		stage_sum += 0.589347779750824;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 12.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(14.0, 14.0, 3.0, 2.0, 3.0);
	if(sum < -0.003550264984369278 * factor)
		stage_sum += 0.43275511264801025;
	else
		stage_sum += 0.5396270155906677;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 12.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 14.0, 3.0, 2.0, 3.0);
	if(sum < -0.019224269315600395 * factor)
		stage_sum += 0.19131340086460114;
	else
		stage_sum += 0.5068330764770508;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 1.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(16.0, 2.0, 4.0, 1.0, 3.0);
	if(sum < 0.0014395059552043676 * factor)
		stage_sum += 0.5308178067207336;
	else
		stage_sum += 0.42435330152511597;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 7.0, 2.0, 10.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 1.0, 5.0, 2.0);
	sum += rect_sum_ii(9.0, 12.0, 1.0, 5.0, 2.0);
	if(sum < -0.00677519990131259 * factor)
		stage_sum += 0.6365395784378052;
	else
		stage_sum += 0.4540086090564728;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 11.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 13.0, 4.0, 2.0, 2.0);
	if(sum < 0.007011963054537773 * factor)
		stage_sum += 0.5189834237098694;
	else
		stage_sum += 0.302619993686676;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 1.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 2.0, 4.0, 1.0, 3.0);
	if(sum < 0.005401465110480785 * factor)
		stage_sum += 0.5105062127113342;
	else
		stage_sum += 0.2557682991027832;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 4.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 5.0, 1.0, 1.0, 3.0);
	if(sum < 0.0009027498890645802 * factor)
		stage_sum += 0.4696914851665497;
	else
		stage_sum += 0.5861827731132507;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 15.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 1.0, 5.0, 3.0);
	if(sum < 0.01147445011883974 * factor)
		stage_sum += 0.5053645968437195;
	else
		stage_sum += 0.15271779894828796;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 5.0, 3.0);
	if(sum < -0.006702343001961708 * factor)
		stage_sum += 0.6508980989456177;
	else
		stage_sum += 0.4890604019165039;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 7.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 1.0, 5.0, 3.0);
	if(sum < -0.0020462959073483944 * factor)
		stage_sum += 0.6241816878318787;
	else
		stage_sum += 0.45146000385284424;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 6.0, 4.0, 14.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 2.0, 14.0, 2.0);
	if(sum < -0.009995156899094582 * factor)
		stage_sum += 0.34327811002731323;
	else
		stage_sum += 0.5400953888893127;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 5.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 7.0, 5.0, 2.0, 3.0);
	if(sum < -0.035700708627700806 * factor)
		stage_sum += 0.1878059059381485;
	else
		stage_sum += 0.5074077844619751;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 3.0, 4.0, 2.0);
	if(sum < 0.0004558456130325794 * factor)
		stage_sum += 0.38052770495414734;
	else
		stage_sum += 0.5402569770812988;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 18.0, 10.0, -1.0);
	sum += rect_sum_ii(6.0, 0.0, 6.0, 10.0, 3.0);
	if(sum < -0.05426060035824776 * factor)
		stage_sum += 0.6843714714050293;
	else
		stage_sum += 0.4595097005367279;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 6.0, 4.0, 14.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 2.0, 14.0, 2.0);
	if(sum < 0.0060600461438298225 * factor)
		stage_sum += 0.5502905249595642;
	else
		stage_sum += 0.45005279779434204;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 4.0, 14.0, -1.0);
	sum += rect_sum_ii(8.0, 6.0, 2.0, 14.0, 2.0);
	if(sum < -0.006479183211922646 * factor)
		stage_sum += 0.33688580989837646;
	else
		stage_sum += 0.5310757160186768;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 4.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 5.0, 1.0, 1.0, 3.0);
	if(sum < -0.0014939469983801246 * factor)
		stage_sum += 0.6487640142440796;
	else
		stage_sum += 0.47561758756637573;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 1.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 1.0, 1.0, 3.0, 2.0);
	if(sum < 0.000014610530342906713 * factor)
		stage_sum += 0.403457909822464;
	else
		stage_sum += 0.5451064109802246;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 1.0, 2.0, 18.0, -1.0);
	sum += rect_sum_ii(19.0, 1.0, 1.0, 9.0, 2.0);
	sum += rect_sum_ii(18.0, 10.0, 1.0, 9.0, 2.0);
	if(sum < -0.00723219383507967 * factor)
		stage_sum += 0.6386873722076416;
	else
		stage_sum += 0.4824739992618561;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 1.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(2.0, 2.0, 4.0, 1.0, 3.0);
	if(sum < -0.004064581822603941 * factor)
		stage_sum += 0.29864218831062317;
	else
		stage_sum += 0.5157335996627808;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 1.0, 2.0, 18.0, -1.0);
	sum += rect_sum_ii(19.0, 1.0, 1.0, 9.0, 2.0);
	sum += rect_sum_ii(18.0, 10.0, 1.0, 9.0, 2.0);
	if(sum < 0.0304630808532238 * factor)
		stage_sum += 0.5022199749946594;
	else
		stage_sum += 0.7159956097602844;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 14.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(1.0, 14.0, 2.0, 3.0, 2.0);
	sum += rect_sum_ii(3.0, 17.0, 2.0, 3.0, 2.0);
	if(sum < -0.008054491132497787 * factor)
		stage_sum += 0.6492452025413513;
	else
		stage_sum += 0.46192750334739685;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 11.0, 7.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 13.0, 7.0, 2.0, 3.0);
	if(sum < 0.039505138993263245 * factor)
		stage_sum += 0.5150570869445801;
	else
		stage_sum += 0.24506139755249023;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 10.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(0.0, 10.0, 3.0, 5.0, 2.0);
	sum += rect_sum_ii(3.0, 15.0, 3.0, 5.0, 2.0);
	if(sum < 0.008453020825982094 * factor)
		stage_sum += 0.4573669135570526;
	else
		stage_sum += 0.6394037008285522;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 0.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 0.0, 1.0, 4.0, 3.0);
	if(sum < -0.0011688120430335402 * factor)
		stage_sum += 0.3865512013435364;
	else
		stage_sum += 0.548366129398346;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 10.0, 5.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 13.0, 5.0, 3.0, 2.0);
	if(sum < 0.002807067008689046 * factor)
		stage_sum += 0.5128579139709473;
	else
		stage_sum += 0.27014800906181335;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 6.0, 1.0, 8.0, -1.0);
	sum += rect_sum_ii(14.0, 10.0, 1.0, 4.0, 2.0);
	if(sum < 0.000473652093205601 * factor)
		stage_sum += 0.4051581919193268;
	else
		stage_sum += 0.5387461185455322;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 18.0, 6.0, -1.0);
	sum += rect_sum_ii(1.0, 7.0, 9.0, 3.0, 2.0);
	sum += rect_sum_ii(10.0, 10.0, 9.0, 3.0, 2.0);
	if(sum < 0.011741080321371555 * factor)
		stage_sum += 0.5295950174331665;
	else
		stage_sum += 0.37194138765335083;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 1.0, 2.0, 2.0);
	if(sum < 0.0031833238899707794 * factor)
		stage_sum += 0.4789406955242157;
	else
		stage_sum += 0.6895126104354858;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 9.0, 4.0, 5.0, -1.0);
	sum += rect_sum_ii(7.0, 9.0, 2.0, 5.0, 2.0);
	if(sum < 0.0007024150108918548 * factor)
		stage_sum += 0.5384489297866821;
	else
		stage_sum += 0.39180809259414673;


	if(stage_sum > 54.62007141113281)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage13(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 2.0, 3.0, 3.0);
	if(sum < 0.01705992966890335 * factor)
		stage_sum += 0.39485278725624084;
	else
		stage_sum += 0.7142534852027893;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 18.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 0.0, 6.0, 4.0, 3.0);
	if(sum < 0.021840840578079224 * factor)
		stage_sum += 0.33703160285949707;
	else
		stage_sum += 0.6090016961097717;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 15.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 17.0, 2.0, 2.0, 2.0);
	if(sum < 0.00024520049919374287 * factor)
		stage_sum += 0.35005760192871094;
	else
		stage_sum += 0.5987902283668518;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 19.0, 9.0, -1.0);
	sum += rect_sum_ii(1.0, 3.0, 19.0, 3.0, 3.0);
	if(sum < 0.008327260613441467 * factor)
		stage_sum += 0.32675281167030334;
	else
		stage_sum += 0.5697240829467773;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 9.0, 3.0, 2.0, 3.0);
	if(sum < 0.0005714829894714057 * factor)
		stage_sum += 0.30445998907089233;
	else
		stage_sum += 0.5531656742095947;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 7.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(15.0, 7.0, 2.0, 2.0, 2.0);
	sum += rect_sum_ii(13.0, 9.0, 2.0, 2.0, 2.0);
	if(sum < 0.0006737398798577487 * factor)
		stage_sum += 0.36500120162963867;
	else
		stage_sum += 0.567263126373291;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 7.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(3.0, 7.0, 2.0, 2.0, 2.0);
	sum += rect_sum_ii(5.0, 9.0, 2.0, 2.0, 2.0);
	if(sum < 0.00003468159047770314 * factor)
		stage_sum += 0.3313541114330292;
	else
		stage_sum += 0.5388727188110352;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 6.0, 10.0, 8.0, -1.0);
	sum += rect_sum_ii(9.0, 10.0, 10.0, 4.0, 2.0);
	if(sum < -0.005856339819729328 * factor)
		stage_sum += 0.2697942852973938;
	else
		stage_sum += 0.5498778820037842;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 8.0, 14.0, 12.0, -1.0);
	sum += rect_sum_ii(3.0, 14.0, 14.0, 6.0, 2.0);
	if(sum < 0.00851022731512785 * factor)
		stage_sum += 0.5269358158111572;
	else
		stage_sum += 0.27628791332244873;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 5.0, 10.0, 12.0, -1.0);
	sum += rect_sum_ii(11.0, 5.0, 5.0, 6.0, 2.0);
	sum += rect_sum_ii(6.0, 11.0, 5.0, 6.0, 2.0);
	if(sum < -0.0698172077536583 * factor)
		stage_sum += 0.29096031188964844;
	else
		stage_sum += 0.5259246826171875;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 11.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 12.0, 2.0, 1.0, 3.0);
	if(sum < -0.0008611367084085941 * factor)
		stage_sum += 0.5892577171325684;
	else
		stage_sum += 0.40736979246139526;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 3.0, 5.0, 2.0);
	if(sum < 0.0009714924963191152 * factor)
		stage_sum += 0.3523564040660858;
	else
		stage_sum += 0.5415862202644348;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 4.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 2.0, 2.0, 2.0);
	if(sum < -0.00001472749045206001 * factor)
		stage_sum += 0.5423017740249634;
	else
		stage_sum += 0.3503156006336212;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 3.0, 5.0, 2.0);
	if(sum < 0.048420291393995285 * factor)
		stage_sum += 0.51939457654953;
	else
		stage_sum += 0.34111958742141724;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 3.0, 5.0, 2.0);
	if(sum < 0.0013257140526548028 * factor)
		stage_sum += 0.31577691435813904;
	else
		stage_sum += 0.5335376262664795;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 2.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(13.0, 2.0, 2.0, 1.0, 3.0);
	if(sum < 0.00001492214960308047 * factor)
		stage_sum += 0.44512999057769775;
	else
		stage_sum += 0.5536553859710693;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 2.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(5.0, 2.0, 2.0, 1.0, 3.0);
	if(sum < -0.002717339899390936 * factor)
		stage_sum += 0.3031741976737976;
	else
		stage_sum += 0.5248088836669922;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 5.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 6.0, 2.0, 1.0, 3.0);
	if(sum < 0.0029219500720500946 * factor)
		stage_sum += 0.4781453013420105;
	else
		stage_sum += 0.6606041789054871;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 10.0, 1.0, 4.0, -1.0);
	sum += rect_sum_ii(0.0, 12.0, 1.0, 2.0, 2.0);
	if(sum < -0.0019804988987743855 * factor)
		stage_sum += 0.31863081455230713;
	else
		stage_sum += 0.5287625193595886;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 5.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 6.0, 2.0, 1.0, 3.0);
	if(sum < -0.004001210909336805 * factor)
		stage_sum += 0.6413596868515015;
	else
		stage_sum += 0.4749928116798401;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 18.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 18.0, 1.0, 2.0, 3.0);
	if(sum < -0.004349199123680592 * factor)
		stage_sum += 0.1507498025894165;
	else
		stage_sum += 0.5098996758460999;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 15.0, 9.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 16.0, 9.0, 1.0, 2.0);
	if(sum < 0.0013490889687091112 * factor)
		stage_sum += 0.4316158890724182;
	else
		stage_sum += 0.5881167054176331;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 4.0, 1.0, 3.0);
	if(sum < 0.0185970701277256 * factor)
		stage_sum += 0.47355538606643677;
	else
		stage_sum += 0.9089794158935547;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 4.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(18.0, 6.0, 2.0, 2.0, 2.0);
	if(sum < -0.001856237999163568 * factor)
		stage_sum += 0.35531890392303467;
	else
		stage_sum += 0.5577837228775024;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 2.0, 1.0, 3.0);
	if(sum < 0.002294043079018593 * factor)
		stage_sum += 0.4500094950199127;
	else
		stage_sum += 0.6580877900123596;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 16.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(15.0, 17.0, 3.0, 1.0, 2.0);
	if(sum < 0.00029982850537635386 * factor)
		stage_sum += 0.5629242062568665;
	else
		stage_sum += 0.3975878953933716;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 3.0, 9.0, -1.0);
	sum += rect_sum_ii(0.0, 3.0, 3.0, 3.0, 3.0);
	if(sum < 0.0035455459728837013 * factor)
		stage_sum += 0.5381547212600708;
	else
		stage_sum += 0.36054858565330505;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 8.0, 3.0, 1.0, 3.0);
	if(sum < 0.009610472247004509 * factor)
		stage_sum += 0.5255997180938721;
	else
		stage_sum += 0.17967459559440613;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 7.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 8.0, 3.0, 1.0, 3.0);
	if(sum < -0.0062783220782876015 * factor)
		stage_sum += 0.227285698056221;
	else
		stage_sum += 0.5114030241966248;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 1.0, 6.0, 2.0);
	if(sum < 0.0034598479978740215 * factor)
		stage_sum += 0.4626308083534241;
	else
		stage_sum += 0.6608219146728516;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 6.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 1.0, 4.0, 3.0);
	if(sum < -0.0013112019514665008 * factor)
		stage_sum += 0.6317539811134338;
	else
		stage_sum += 0.4436857998371124;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 8.0, 12.0, -1.0);
	sum += rect_sum_ii(11.0, 6.0, 4.0, 6.0, 2.0);
	sum += rect_sum_ii(7.0, 12.0, 4.0, 6.0, 2.0);
	if(sum < 0.002687617903575301 * factor)
		stage_sum += 0.5421109795570374;
	else
		stage_sum += 0.40540221333503723;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 8.0, 12.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 4.0, 6.0, 2.0);
	sum += rect_sum_ii(9.0, 12.0, 4.0, 6.0, 2.0);
	if(sum < 0.003911816980689764 * factor)
		stage_sum += 0.5358477830886841;
	else
		stage_sum += 0.32734549045562744;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 4.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 5.0, 3.0, 1.0, 3.0);
	if(sum < -0.014206450432538986 * factor)
		stage_sum += 0.7793576717376709;
	else
		stage_sum += 0.49757811427116394;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 16.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 17.0, 3.0, 1.0, 2.0);
	if(sum < 0.0007170552853494883 * factor)
		stage_sum += 0.5297319889068604;
	else
		stage_sum += 0.35609039664268494;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 4.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 5.0, 3.0, 1.0, 3.0);
	if(sum < 0.001663501956500113 * factor)
		stage_sum += 0.46780940890312195;
	else
		stage_sum += 0.5816481709480286;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 12.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(2.0, 14.0, 6.0, 2.0, 3.0);
	if(sum < 0.0033686188980937004 * factor)
		stage_sum += 0.5276734232902527;
	else
		stage_sum += 0.3446420133113861;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 13.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 14.0, 6.0, 1.0, 3.0);
	if(sum < 0.012799530290067196 * factor)
		stage_sum += 0.4834679961204529;
	else
		stage_sum += 0.7472159266471863;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 14.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 15.0, 6.0, 1.0, 3.0);
	if(sum < 0.0033901201095432043 * factor)
		stage_sum += 0.4511859118938446;
	else
		stage_sum += 0.6401721239089966;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 15.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(14.0, 16.0, 5.0, 1.0, 3.0);
	if(sum < 0.004707077983766794 * factor)
		stage_sum += 0.533565878868103;
	else
		stage_sum += 0.355522096157074;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 5.0, 3.0, 1.0, 3.0);
	if(sum < 0.0014819339849054813 * factor)
		stage_sum += 0.42507070302963257;
	else
		stage_sum += 0.5772724151611328;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 15.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(14.0, 16.0, 5.0, 1.0, 3.0);
	if(sum < -0.0069995759986341 * factor)
		stage_sum += 0.3003320097923279;
	else
		stage_sum += 0.5292900204658508;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 3.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 3.0, 2.0, 2.0, 3.0);
	if(sum < 0.015939010307192802 * factor)
		stage_sum += 0.5067319273948669;
	else
		stage_sum += 0.1675581932067871;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 15.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 16.0, 4.0, 1.0, 3.0);
	if(sum < 0.007637734990566969 * factor)
		stage_sum += 0.4795069992542267;
	else
		stage_sum += 0.7085601091384888;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 15.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 16.0, 5.0, 1.0, 3.0);
	if(sum < 0.006733404006808996 * factor)
		stage_sum += 0.5133113265037537;
	else
		stage_sum += 0.21624700725078583;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 13.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 13.0, 2.0, 3.0, 2.0);
	sum += rect_sum_ii(8.0, 16.0, 2.0, 3.0, 2.0);
	if(sum < -0.012858809903264046 * factor)
		stage_sum += 0.19388419389724731;
	else
		stage_sum += 0.525137186050415;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 8.0, 1.0, 3.0, 3.0);
	if(sum < -0.0006227080011740327 * factor)
		stage_sum += 0.5686538219451904;
	else
		stage_sum += 0.41978681087493896;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 0.0, 5.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 2.0, 5.0, 2.0, 2.0);
	if(sum < -0.0005265168147161603 * factor)
		stage_sum += 0.42241689562797546;
	else
		stage_sum += 0.5429695844650269;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 20.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 2.0, 10.0, 1.0, 2.0);
	sum += rect_sum_ii(10.0, 3.0, 10.0, 1.0, 2.0);
	if(sum < 0.011075099930167198 * factor)
		stage_sum += 0.5113775134086609;
	else
		stage_sum += 0.2514517903327942;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 18.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 0.0, 6.0, 4.0, 3.0);
	if(sum < -0.03672825172543526 * factor)
		stage_sum += 0.7194662094116211;
	else
		stage_sum += 0.4849618971347809;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 3.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(6.0, 3.0, 2.0, 1.0, 3.0);
	if(sum < -0.00028207109426148236 * factor)
		stage_sum += 0.3840261995792389;
	else
		stage_sum += 0.539444625377655;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 18.0, 13.0, 2.0, -1.0);
	sum += rect_sum_ii(4.0, 19.0, 13.0, 1.0, 2.0);
	if(sum < -0.0027489690110087395 * factor)
		stage_sum += 0.593708872795105;
	else
		stage_sum += 0.45691820979118347;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 10.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(2.0, 12.0, 3.0, 2.0, 3.0);
	if(sum < 0.010047519579529762 * factor)
		stage_sum += 0.5138576030731201;
	else
		stage_sum += 0.2802298069000244;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 12.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(17.0, 12.0, 3.0, 4.0, 2.0);
	sum += rect_sum_ii(14.0, 16.0, 3.0, 4.0, 2.0);
	if(sum < -0.008149784058332443 * factor)
		stage_sum += 0.6090037226676941;
	else
		stage_sum += 0.4636121094226837;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 13.0, 10.0, 6.0, -1.0);
	sum += rect_sum_ii(4.0, 13.0, 5.0, 3.0, 2.0);
	sum += rect_sum_ii(9.0, 16.0, 5.0, 3.0, 2.0);
	if(sum < -0.006883388850837946 * factor)
		stage_sum += 0.3458611071109772;
	else
		stage_sum += 0.5254660248756409;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 12.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(14.0, 13.0, 1.0, 1.0, 2.0);
	if(sum < -0.0000140393603942357 * factor)
		stage_sum += 0.5693104267120361;
	else
		stage_sum += 0.40820831060409546;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 13.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 14.0, 4.0, 1.0, 3.0);
	if(sum < 0.001549841952510178 * factor)
		stage_sum += 0.4350537061691284;
	else
		stage_sum += 0.5806517004966736;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 12.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(14.0, 13.0, 2.0, 1.0, 2.0);
	if(sum < -0.006784149911254644 * factor)
		stage_sum += 0.14688730239868164;
	else
		stage_sum += 0.5182775259017944;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 12.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(4.0, 13.0, 2.0, 1.0, 2.0);
	if(sum < 0.00021705629478674382 * factor)
		stage_sum += 0.5293524265289307;
	else
		stage_sum += 0.345617413520813;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 9.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 13.0, 9.0, 1.0, 2.0);
	if(sum < 0.00031198898795992136 * factor)
		stage_sum += 0.4652450978755951;
	else
		stage_sum += 0.5942413806915283;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 14.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 15.0, 2.0, 1.0, 3.0);
	if(sum < 0.005450753029435873 * factor)
		stage_sum += 0.4653508961200714;
	else
		stage_sum += 0.7024846076965332;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 10.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(11.0, 13.0, 3.0, 3.0, 2.0);
	if(sum < -0.00025818689027801156 * factor)
		stage_sum += 0.5497295260429382;
	else
		stage_sum += 0.3768967092037201;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 9.0, 12.0, -1.0);
	sum += rect_sum_ii(5.0, 12.0, 9.0, 6.0, 2.0);
	if(sum < -0.01744253933429718 * factor)
		stage_sum += 0.39190879464149475;
	else
		stage_sum += 0.5457497835159302;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 10.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(11.0, 13.0, 3.0, 3.0, 2.0);
	if(sum < -0.04534352943301201 * factor)
		stage_sum += 0.16313570737838745;
	else
		stage_sum += 0.5154908895492554;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 10.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 13.0, 3.0, 3.0, 2.0);
	if(sum < 0.0019190689781680703 * factor)
		stage_sum += 0.514589786529541;
	else
		stage_sum += 0.2791895866394043;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 11.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 5.0, 11.0, 1.0, 3.0);
	if(sum < -0.006017786916345358 * factor)
		stage_sum += 0.6517636179924011;
	else
		stage_sum += 0.47563329339027405;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 1.0, 5.0, 10.0, -1.0);
	sum += rect_sum_ii(7.0, 6.0, 5.0, 5.0, 2.0);
	if(sum < -0.004072073847055435 * factor)
		stage_sum += 0.5514652729034424;
	else
		stage_sum += 0.4092685878276825;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 8.0, 18.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 9.0, 18.0, 1.0, 2.0);
	if(sum < 0.00039855059003457427 * factor)
		stage_sum += 0.31652408838272095;
	else
		stage_sum += 0.5285550951957703;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 17.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 18.0, 5.0, 1.0, 3.0);
	if(sum < -0.0065418570302426815 * factor)
		stage_sum += 0.6853377819061279;
	else
		stage_sum += 0.4652808904647827;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 9.0, 12.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 9.0, 4.0, 1.0, 3.0);
	if(sum < 0.003484508953988552 * factor)
		stage_sum += 0.5484588146209717;
	else
		stage_sum += 0.4502759873867035;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 14.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 3.0, 3.0, 2.0);
	sum += rect_sum_ii(3.0, 17.0, 3.0, 3.0, 2.0);
	if(sum < -0.013696780428290367 * factor)
		stage_sum += 0.6395779848098755;
	else
		stage_sum += 0.4572555124759674;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 9.0, 12.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 9.0, 4.0, 1.0, 3.0);
	if(sum < -0.017347140237689018 * factor)
		stage_sum += 0.2751072943210602;
	else
		stage_sum += 0.5181614756584167;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 9.0, 12.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 9.0, 4.0, 1.0, 3.0);
	if(sum < -0.004088542889803648 * factor)
		stage_sum += 0.3325636088848114;
	else
		stage_sum += 0.5194984078407288;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 10.0, 6.0, 7.0, -1.0);
	sum += rect_sum_ii(14.0, 10.0, 3.0, 7.0, 2.0);
	if(sum < -0.009468790143728256 * factor)
		stage_sum += 0.5942280888557434;
	else
		stage_sum += 0.485181987285614;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 16.0, 2.0, -1.0);
	sum += rect_sum_ii(1.0, 1.0, 16.0, 1.0, 2.0);
	if(sum < 0.0017084840219467878 * factor)
		stage_sum += 0.41671109199523926;
	else
		stage_sum += 0.5519806146621704;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 9.0, 10.0, 9.0, -1.0);
	sum += rect_sum_ii(10.0, 12.0, 10.0, 3.0, 3.0);
	if(sum < 0.009480909444391727 * factor)
		stage_sum += 0.5433894991874695;
	else
		stage_sum += 0.4208514988422394;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 1.0, 10.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 1.0, 5.0, 2.0, 2.0);
	if(sum < -0.004738965071737766 * factor)
		stage_sum += 0.6407189965248108;
	else
		stage_sum += 0.45606550574302673;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 3.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(17.0, 4.0, 2.0, 1.0, 3.0);
	if(sum < 0.006576105020940304 * factor)
		stage_sum += 0.5214555263519287;
	else
		stage_sum += 0.22582270205020905;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 3.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 4.0, 2.0, 1.0, 3.0);
	if(sum < -0.0021690549328923225 * factor)
		stage_sum += 0.3151527941226959;
	else
		stage_sum += 0.5156704783439636;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 6.0, 3.0);
	if(sum < 0.014660170301795006 * factor)
		stage_sum += 0.48708370327949524;
	else
		stage_sum += 0.668994128704071;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 5.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 2.0, 3.0, 2.0);
	if(sum < 0.00017231999663636088 * factor)
		stage_sum += 0.35697489976882935;
	else
		stage_sum += 0.5251078009605408;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 5.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 2.0, 6.0, 3.0);
	if(sum < -0.021803760901093483 * factor)
		stage_sum += 0.8825920820236206;
	else
		stage_sum += 0.49663299322128296;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 4.0, 12.0, 12.0, -1.0);
	sum += rect_sum_ii(3.0, 4.0, 6.0, 6.0, 2.0);
	sum += rect_sum_ii(9.0, 10.0, 6.0, 6.0, 2.0);
	if(sum < -0.09473610669374466 * factor)
		stage_sum += 0.14461620151996613;
	else
		stage_sum += 0.5061113834381104;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 2.0, 6.0, 15.0, -1.0);
	sum += rect_sum_ii(11.0, 2.0, 2.0, 15.0, 3.0);
	if(sum < 0.0055825551971793175 * factor)
		stage_sum += 0.5396478772163391;
	else
		stage_sum += 0.4238066077232361;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 2.0, 6.0, 17.0, -1.0);
	sum += rect_sum_ii(4.0, 2.0, 2.0, 17.0, 3.0);
	if(sum < 0.001951709040440619 * factor)
		stage_sum += 0.4170410931110382;
	else
		stage_sum += 0.5497786998748779;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 10.0, 6.0, 7.0, -1.0);
	sum += rect_sum_ii(14.0, 10.0, 3.0, 7.0, 2.0);
	if(sum < 0.012149900197982788 * factor)
		stage_sum += 0.4698367118835449;
	else
		stage_sum += 0.5664274096488953;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 10.0, 6.0, 7.0, -1.0);
	sum += rect_sum_ii(3.0, 10.0, 3.0, 7.0, 2.0);
	if(sum < -0.007516962010413408 * factor)
		stage_sum += 0.6267772912979126;
	else
		stage_sum += 0.4463135898113251;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 2.0, 6.0, 15.0, -1.0);
	sum += rect_sum_ii(11.0, 2.0, 2.0, 15.0, 3.0);
	if(sum < -0.07166790962219238 * factor)
		stage_sum += 0.3097011148929596;
	else
		stage_sum += 0.5221003293991089;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 2.0, 6.0, 15.0, -1.0);
	sum += rect_sum_ii(7.0, 2.0, 2.0, 15.0, 3.0);
	if(sum < -0.08829241991043091 * factor)
		stage_sum += 0.08112388849258423;
	else
		stage_sum += 0.5006365180015564;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 9.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(17.0, 11.0, 3.0, 2.0, 3.0);
	if(sum < 0.031063079833984375 * factor)
		stage_sum += 0.5155503749847412;
	else
		stage_sum += 0.12822559475898743;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 7.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 2.0, 6.0, 3.0);
	if(sum < 0.046621840447187424 * factor)
		stage_sum += 0.46997779607772827;
	else
		stage_sum += 0.736396074295044;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 10.0, 18.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 10.0, 9.0, 3.0, 2.0);
	sum += rect_sum_ii(1.0, 13.0, 9.0, 3.0, 2.0);
	if(sum < -0.012189489789307117 * factor)
		stage_sum += 0.3920530080795288;
	else
		stage_sum += 0.5518996715545654;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 9.0, 10.0, 9.0, -1.0);
	sum += rect_sum_ii(0.0, 12.0, 10.0, 3.0, 3.0);
	if(sum < 0.0130161102861166 * factor)
		stage_sum += 0.5260658264160156;
	else
		stage_sum += 0.3685136139392853;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 15.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 16.0, 4.0, 1.0, 3.0);
	if(sum < -0.003495289944112301 * factor)
		stage_sum += 0.6339294910430908;
	else
		stage_sum += 0.4716280996799469;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 12.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(5.0, 14.0, 3.0, 2.0, 2.0);
	if(sum < -0.00004401503974804655 * factor)
		stage_sum += 0.5333027243614197;
	else
		stage_sum += 0.3776184916496277;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 3.0, 16.0, 12.0, -1.0);
	sum += rect_sum_ii(3.0, 9.0, 16.0, 6.0, 2.0);
	if(sum < -0.1096649020910263 * factor)
		stage_sum += 0.17653420567512512;
	else
		stage_sum += 0.5198346972465515;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 1.0, 12.0, 12.0, -1.0);
	sum += rect_sum_ii(1.0, 1.0, 6.0, 6.0, 2.0);
	sum += rect_sum_ii(7.0, 7.0, 6.0, 6.0, 2.0);
	if(sum < -0.0009027955820783973 * factor)
		stage_sum += 0.5324159860610962;
	else
		stage_sum += 0.3838908076286316;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 4.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 4.0, 1.0, 2.0, 2.0);
	sum += rect_sum_ii(10.0, 6.0, 1.0, 2.0, 2.0);
	if(sum < 0.0007112664170563221 * factor)
		stage_sum += 0.46479299664497375;
	else
		stage_sum += 0.5755224227905273;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 9.0, 10.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 9.0, 5.0, 1.0, 2.0);
	sum += rect_sum_ii(5.0, 10.0, 5.0, 1.0, 2.0);
	if(sum < -0.003125027986243367 * factor)
		stage_sum += 0.323670893907547;
	else
		stage_sum += 0.5166770815849304;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 11.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 12.0, 3.0, 1.0, 3.0);
	if(sum < 0.002414467977359891 * factor)
		stage_sum += 0.47874391078948975;
	else
		stage_sum += 0.6459717750549316;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 12.0, 9.0, 2.0, -1.0);
	sum += rect_sum_ii(3.0, 13.0, 9.0, 1.0, 2.0);
	if(sum < 0.00044391240226104856 * factor)
		stage_sum += 0.4409308135509491;
	else
		stage_sum += 0.6010255813598633;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 9.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 10.0, 2.0, 1.0, 2.0);
	if(sum < -0.0002261118934256956 * factor)
		stage_sum += 0.40381139516830444;
	else
		stage_sum += 0.5493255853652954;


	if(stage_sum > 50.16973114013672)
		return 1;
	else
		return 0;
}

int HaarCascadeFrontalFaceAlt_stage14(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 4.0, 13.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 6.0, 13.0, 2.0, 3.0);
	if(sum < -0.046901289373636246 * factor)
		stage_sum += 0.660017192363739;
	else
		stage_sum += 0.37438011169433594;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 7.0, 3.0, 2.0, 2.0);
	sum += rect_sum_ii(9.0, 9.0, 3.0, 2.0, 2.0);
	if(sum < -0.001456834957934916 * factor)
		stage_sum += 0.578399121761322;
	else
		stage_sum += 0.34377971291542053;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(4.0, 0.0, 3.0, 8.0, 2.0);
	if(sum < 0.005559836979955435 * factor)
		stage_sum += 0.3622266948223114;
	else
		stage_sum += 0.5908216238021851;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 2.0, 12.0, -1.0);
	sum += rect_sum_ii(9.0, 11.0, 2.0, 6.0, 2.0);
	if(sum < 0.0007317048730328679 * factor)
		stage_sum += 0.550041913986206;
	else
		stage_sum += 0.28735581040382385;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 3.0, 10.0, -1.0);
	sum += rect_sum_ii(4.0, 9.0, 3.0, 5.0, 2.0);
	if(sum < 0.001331800944171846 * factor)
		stage_sum += 0.267316997051239;
	else
		stage_sum += 0.5431019067764282;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 17.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 18.0, 8.0, 1.0, 3.0);
	if(sum < 0.00024347059661522508 * factor)
		stage_sum += 0.38550278544425964;
	else
		stage_sum += 0.574138879776001;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 10.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 7.0, 10.0, 2.0, 3.0);
	if(sum < -0.0030512469820678234 * factor)
		stage_sum += 0.5503209829330444;
	else
		stage_sum += 0.34628450870513916;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 2.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(13.0, 3.0, 3.0, 1.0, 2.0);
	if(sum < -0.0006865719915367663 * factor)
		stage_sum += 0.3291221857070923;
	else
		stage_sum += 0.5429509282112122;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 5.0, 4.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 2.0, 5.0, 2.0);
	if(sum < 0.001466820016503334 * factor)
		stage_sum += 0.35883820056915283;
	else
		stage_sum += 0.5351811051368713;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 14.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(12.0, 16.0, 3.0, 2.0, 3.0);
	if(sum < 0.0003202187072020024 * factor)
		stage_sum += 0.42968419194221497;
	else
		stage_sum += 0.5700234174728394;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 11.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(1.0, 12.0, 8.0, 1.0, 2.0);
	if(sum < 0.0007412218837998807 * factor)
		stage_sum += 0.5282164812088013;
	else
		stage_sum += 0.3366870880126953;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 13.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 14.0, 6.0, 1.0, 3.0);
	if(sum < 0.0038330298848450184 * factor)
		stage_sum += 0.4559567868709564;
	else
		stage_sum += 0.6257336139678955;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 7.0, 3.0, 2.0, 3.0);
	if(sum < -0.015456439927220345 * factor)
		stage_sum += 0.23501169681549072;
	else
		stage_sum += 0.512945294380188;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 2.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(13.0, 3.0, 3.0, 1.0, 2.0);
	if(sum < 0.002679677912965417 * factor)
		stage_sum += 0.5329415202140808;
	else
		stage_sum += 0.4155062139034271;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 14.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(4.0, 14.0, 2.0, 3.0, 2.0);
	sum += rect_sum_ii(6.0, 17.0, 2.0, 3.0, 2.0);
	if(sum < 0.0028296569362282753 * factor)
		stage_sum += 0.4273087978363037;
	else
		stage_sum += 0.5804538130760193;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 2.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(13.0, 3.0, 3.0, 1.0, 2.0);
	if(sum < -0.0039444249123334885 * factor)
		stage_sum += 0.2912611961364746;
	else
		stage_sum += 0.5202686190605164;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 2.0, 4.0, 12.0, -1.0);
	sum += rect_sum_ii(8.0, 6.0, 4.0, 4.0, 3.0);
	if(sum < 0.002717955969274044 * factor)
		stage_sum += 0.5307688117027283;
	else
		stage_sum += 0.3585677146911621;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 0.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(17.0, 0.0, 3.0, 4.0, 2.0);
	sum += rect_sum_ii(14.0, 4.0, 3.0, 4.0, 2.0);
	if(sum < 0.005907762795686722 * factor)
		stage_sum += 0.47037750482559204;
	else
		stage_sum += 0.5941585898399353;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 17.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 17.0, 1.0, 2.0, 3.0);
	if(sum < -0.004224034957587719 * factor)
		stage_sum += 0.21415670216083527;
	else
		stage_sum += 0.5088796019554138;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 13.0, 4.0, 1.0, 2.0);
	if(sum < 0.0040725888684391975 * factor)
		stage_sum += 0.47664138674736023;
	else
		stage_sum += 0.6841061115264893;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 8.0, 12.0, -1.0);
	sum += rect_sum_ii(6.0, 0.0, 4.0, 6.0, 2.0);
	sum += rect_sum_ii(10.0, 6.0, 4.0, 6.0, 2.0);
	if(sum < 0.01014953013509512 * factor)
		stage_sum += 0.5360798835754395;
	else
		stage_sum += 0.37484970688819885;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 0.0, 2.0, 10.0, -1.0);
	sum += rect_sum_ii(15.0, 0.0, 1.0, 5.0, 2.0);
	sum += rect_sum_ii(14.0, 5.0, 1.0, 5.0, 2.0);
	if(sum < -0.00018864999583456665 * factor)
		stage_sum += 0.5720130205154419;
	else
		stage_sum += 0.38538050651550293;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 3.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 3.0, 4.0, 3.0, 2.0);
	sum += rect_sum_ii(9.0, 6.0, 4.0, 3.0, 2.0);
	if(sum < -0.0048864358104765415 * factor)
		stage_sum += 0.3693122863769531;
	else
		stage_sum += 0.5340958833694458;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 0.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(17.0, 0.0, 3.0, 5.0, 2.0);
	sum += rect_sum_ii(14.0, 5.0, 3.0, 5.0, 2.0);
	if(sum < 0.02615847997367382 * factor)
		stage_sum += 0.49623748660087585;
	else
		stage_sum += 0.6059989929199219;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 14.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 15.0, 1.0, 1.0, 2.0);
	if(sum < 0.0004856075975112617 * factor)
		stage_sum += 0.4438945949077606;
	else
		stage_sum += 0.6012468934059143;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 10.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 11.0, 4.0, 1.0, 3.0);
	if(sum < 0.011268709786236286 * factor)
		stage_sum += 0.5244250297546387;
	else
		stage_sum += 0.18403880298137665;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 2.0, 1.0, 3.0);
	if(sum < -0.0028114619199186563 * factor)
		stage_sum += 0.6060283780097961;
	else
		stage_sum += 0.4409897029399872;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 13.0, 14.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 13.0, 7.0, 2.0, 2.0);
	sum += rect_sum_ii(3.0, 15.0, 7.0, 2.0, 2.0);
	if(sum < -0.005611272994428873 * factor)
		stage_sum += 0.3891170918941498;
	else
		stage_sum += 0.5589237213134766;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 10.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 11.0, 4.0, 1.0, 3.0);
	if(sum < 0.008568009361624718 * factor)
		stage_sum += 0.5069345831871033;
	else
		stage_sum += 0.20626190304756165;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 11.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(11.0, 11.0, 2.0, 1.0, 3.0);
	if(sum < -0.00038172779022715986 * factor)
		stage_sum += 0.5882201790809631;
	else
		stage_sum += 0.41926109790802;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 11.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 11.0, 2.0, 1.0, 3.0);
	if(sum < -0.00017680290329735726 * factor)
		stage_sum += 0.5533605813980103;
	else
		stage_sum += 0.400336891412735;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 5.0, 16.0, 15.0, -1.0);
	sum += rect_sum_ii(3.0, 10.0, 16.0, 5.0, 3.0);
	if(sum < 0.006511253770440817 * factor)
		stage_sum += 0.3310146927833557;
	else
		stage_sum += 0.5444191098213196;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 12.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 12.0, 2.0, 2.0, 2.0);
	if(sum < -0.00006594868318643421 * factor)
		stage_sum += 0.5433831810951233;
	else
		stage_sum += 0.3944905996322632;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 12.0, 10.0, -1.0);
	sum += rect_sum_ii(10.0, 4.0, 6.0, 5.0, 2.0);
	sum += rect_sum_ii(4.0, 9.0, 6.0, 5.0, 2.0);
	if(sum < 0.006993905175477266 * factor)
		stage_sum += 0.5600358247756958;
	else
		stage_sum += 0.41927140951156616;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 6.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 1.0, 4.0, 3.0);
	if(sum < -0.0046744439750909805 * factor)
		stage_sum += 0.6685466766357422;
	else
		stage_sum += 0.46049609780311584;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 12.0, 4.0, 8.0, -1.0);
	sum += rect_sum_ii(10.0, 12.0, 2.0, 4.0, 2.0);
	sum += rect_sum_ii(8.0, 16.0, 2.0, 4.0, 2.0);
	if(sum < 0.011589850299060345 * factor)
		stage_sum += 0.5357121229171753;
	else
		stage_sum += 0.2926830053329468;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 4.0, 1.0, 3.0);
	if(sum < 0.013007840141654015 * factor)
		stage_sum += 0.4679817855358124;
	else
		stage_sum += 0.730746328830719;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 2.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(13.0, 2.0, 1.0, 2.0, 3.0);
	if(sum < -0.0011008579749614 * factor)
		stage_sum += 0.3937501013278961;
	else
		stage_sum += 0.5415065288543701;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 15.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 16.0, 3.0, 1.0, 2.0);
	if(sum < 0.0006047264905646443 * factor)
		stage_sum += 0.42423760890960693;
	else
		stage_sum += 0.5604041218757629;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 9.0, 14.0, -1.0);
	sum += rect_sum_ii(9.0, 0.0, 3.0, 14.0, 3.0);
	if(sum < -0.014494840055704117 * factor)
		stage_sum += 0.36312100291252136;
	else
		stage_sum += 0.5293182730674744;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 6.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 1.0, 3.0, 2.0);
	if(sum < -0.005305694881826639 * factor)
		stage_sum += 0.686045229434967;
	else
		stage_sum += 0.46218210458755493;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 8.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 9.0, 2.0, 1.0, 3.0);
	if(sum < -0.00081829127157107 * factor)
		stage_sum += 0.3944096863269806;
	else
		stage_sum += 0.542043924331665;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 9.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 11.0, 4.0, 2.0, 3.0);
	if(sum < -0.019077520817518234 * factor)
		stage_sum += 0.1962621957063675;
	else
		stage_sum += 0.5037891864776611;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 1.0, 8.0, 1.0, 2.0);
	if(sum < 0.00035549470339901745 * factor)
		stage_sum += 0.40862590074539185;
	else
		stage_sum += 0.5613973140716553;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 14.0, 7.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 15.0, 7.0, 1.0, 3.0);
	if(sum < 0.0019679730758070946 * factor)
		stage_sum += 0.448912113904953;
	else
		stage_sum += 0.5926123261451721;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 10.0, 8.0, 9.0, -1.0);
	sum += rect_sum_ii(8.0, 13.0, 8.0, 3.0, 3.0);
	if(sum < 0.006918914150446653 * factor)
		stage_sum += 0.5335925817489624;
	else
		stage_sum += 0.3728385865688324;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 2.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 2.0, 1.0, 2.0, 3.0);
	if(sum < 0.002987277926877141 * factor)
		stage_sum += 0.5111321210861206;
	else
		stage_sum += 0.29756438732147217;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 1.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(17.0, 1.0, 3.0, 4.0, 2.0);
	sum += rect_sum_ii(14.0, 5.0, 3.0, 4.0, 2.0);
	if(sum < -0.006226461846381426 * factor)
		stage_sum += 0.5541489720344543;
	else
		stage_sum += 0.4824537932872772;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 1.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(0.0, 1.0, 3.0, 4.0, 2.0);
	sum += rect_sum_ii(3.0, 5.0, 3.0, 4.0, 2.0);
	if(sum < 0.013353300280869007 * factor)
		stage_sum += 0.4586423933506012;
	else
		stage_sum += 0.6414797902107239;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 2.0, 18.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 2.0, 9.0, 3.0, 2.0);
	sum += rect_sum_ii(1.0, 5.0, 9.0, 3.0, 2.0);
	if(sum < 0.033505238592624664 * factor)
		stage_sum += 0.5392425060272217;
	else
		stage_sum += 0.34299948811531067;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 3.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(10.0, 3.0, 1.0, 1.0, 2.0);
	if(sum < -0.0025294460356235504 * factor)
		stage_sum += 0.1703713983297348;
	else
		stage_sum += 0.5013315081596375;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 2.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(15.0, 2.0, 2.0, 3.0, 2.0);
	sum += rect_sum_ii(13.0, 5.0, 2.0, 3.0, 2.0);
	if(sum < -0.001280162949115038 * factor)
		stage_sum += 0.5305461883544922;
	else
		stage_sum += 0.46974050998687744;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 5.0, 3.0, 1.0, 3.0);
	if(sum < 0.007068738806992769 * factor)
		stage_sum += 0.4615545868873596;
	else
		stage_sum += 0.643650472164154;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 5.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 6.0, 1.0, 1.0, 3.0);
	if(sum < 0.0009688049904070795 * factor)
		stage_sum += 0.4833599030971527;
	else
		stage_sum += 0.6043894290924072;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 16.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(2.0, 17.0, 5.0, 1.0, 3.0);
	if(sum < 0.003964765928685665 * factor)
		stage_sum += 0.5187637209892273;
	else
		stage_sum += 0.323181688785553;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 2.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(15.0, 2.0, 2.0, 3.0, 2.0);
	sum += rect_sum_ii(13.0, 5.0, 2.0, 3.0, 2.0);
	if(sum < -0.022057730704545975 * factor)
		stage_sum += 0.40792569518089294;
	else
		stage_sum += 0.520098090171814;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 2.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 2.0, 2.0, 3.0, 2.0);
	sum += rect_sum_ii(5.0, 5.0, 2.0, 3.0, 2.0);
	if(sum < -0.0006690631271339953 * factor)
		stage_sum += 0.533160924911499;
	else
		stage_sum += 0.3815600872039795;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 5.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(13.0, 6.0, 1.0, 1.0, 2.0);
	if(sum < -0.0006700932863168418 * factor)
		stage_sum += 0.5655422210693359;
	else
		stage_sum += 0.4688901901245117;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 2.0, 1.0, 2.0);
	if(sum < 0.000742845528293401 * factor)
		stage_sum += 0.4534381031990051;
	else
		stage_sum += 0.6287400126457214;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 9.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(13.0, 9.0, 1.0, 2.0, 2.0);
	if(sum < 0.0022227810695767403 * factor)
		stage_sum += 0.5350633263587952;
	else
		stage_sum += 0.3303655982017517;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 9.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 9.0, 1.0, 2.0, 2.0);
	if(sum < -0.005413052160292864 * factor)
		stage_sum += 0.11136870086193085;
	else
		stage_sum += 0.500543475151062;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 17.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(13.0, 18.0, 3.0, 1.0, 2.0);
	if(sum < -0.000014520040167553816 * factor)
		stage_sum += 0.5628737807273865;
	else
		stage_sum += 0.43251338601112366;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 16.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(6.0, 16.0, 2.0, 2.0, 2.0);
	sum += rect_sum_ii(8.0, 18.0, 2.0, 2.0, 2.0);
	if(sum < 0.00023369169502984732 * factor)
		stage_sum += 0.41658350825309753;
	else
		stage_sum += 0.5447791218757629;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 16.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 17.0, 2.0, 1.0, 3.0);
	if(sum < 0.004289454780519009 * factor)
		stage_sum += 0.48603910207748413;
	else
		stage_sum += 0.6778649091720581;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 13.0, 9.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 15.0, 9.0, 2.0, 3.0);
	if(sum < 0.0059103150852024555 * factor)
		stage_sum += 0.52623051404953;
	else
		stage_sum += 0.3612113893032074;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 14.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 17.0, 2.0, 3.0, 2.0);
	if(sum < 0.012900539673864841 * factor)
		stage_sum += 0.5319377183914185;
	else
		stage_sum += 0.32502880692481995;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 15.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 16.0, 2.0, 1.0, 3.0);
	if(sum < 0.004698297940194607 * factor)
		stage_sum += 0.461824506521225;
	else
		stage_sum += 0.6665925979614258;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 10.0, 18.0, 6.0, -1.0);
	sum += rect_sum_ii(1.0, 12.0, 18.0, 2.0, 3.0);
	if(sum < 0.010439859703183174 * factor)
		stage_sum += 0.550567090511322;
	else
		stage_sum += 0.3883604109287262;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 11.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 12.0, 4.0, 1.0, 2.0);
	if(sum < 0.0030443191062659025 * factor)
		stage_sum += 0.46978530287742615;
	else
		stage_sum += 0.7301844954490662;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 9.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 10.0, 6.0, 1.0, 2.0);
	if(sum < -0.0006159375188872218 * factor)
		stage_sum += 0.38308390974998474;
	else
		stage_sum += 0.5464984178543091;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 8.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 9.0, 2.0, 1.0, 3.0);
	if(sum < -0.0034247159492224455 * factor)
		stage_sum += 0.256630003452301;
	else
		stage_sum += 0.5089530944824219;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 5.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(18.0, 5.0, 1.0, 4.0, 3.0);
	if(sum < -0.009353856556117535 * factor)
		stage_sum += 0.6469966173171997;
	else
		stage_sum += 0.49407958984375;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 19.0, 18.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 19.0, 6.0, 1.0, 3.0);
	if(sum < 0.05233899876475334 * factor)
		stage_sum += 0.4745982885360718;
	else
		stage_sum += 0.787877082824707;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 0.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 0.0, 1.0, 2.0, 3.0);
	if(sum < 0.0035765620414167643 * factor)
		stage_sum += 0.5306664705276489;
	else
		stage_sum += 0.2748498022556305;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 8.0, 1.0, 6.0, -1.0);
	sum += rect_sum_ii(1.0, 10.0, 1.0, 2.0, 3.0);
	if(sum < 0.0007155531784519553 * factor)
		stage_sum += 0.541312575340271;
	else
		stage_sum += 0.40419089794158936;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 17.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 17.0, 4.0, 3.0, 2.0);
	if(sum < -0.010516679845750332 * factor)
		stage_sum += 0.6158512234687805;
	else
		stage_sum += 0.48152831196784973;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(1.0, 5.0, 1.0, 4.0, 3.0);
	if(sum < 0.007734792772680521 * factor)
		stage_sum += 0.46958059072494507;
	else
		stage_sum += 0.7028980851173401;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 8.0, 2.0, 1.0, 3.0);
	if(sum < -0.004322677850723267 * factor)
		stage_sum += 0.28495660424232483;
	else
		stage_sum += 0.5304684042930603;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 11.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 11.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(8.0, 12.0, 1.0, 1.0, 2.0);
	if(sum < -0.0025534399319440126 * factor)
		stage_sum += 0.7056984901428223;
	else
		stage_sum += 0.4688892066478729;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 3.0, 2.0, 5.0, -1.0);
	sum += rect_sum_ii(11.0, 3.0, 1.0, 5.0, 2.0);
	if(sum < 0.00010268510231981054 * factor)
		stage_sum += 0.3902932107448578;
	else
		stage_sum += 0.5573464035987854;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 3.0, 2.0, 5.0, -1.0);
	sum += rect_sum_ii(8.0, 3.0, 1.0, 5.0, 2.0);
	if(sum < 0.000007139518857002258 * factor)
		stage_sum += 0.368423193693161;
	else
		stage_sum += 0.526398777961731;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 13.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 14.0, 2.0, 1.0, 3.0);
	if(sum < -0.0016711989883333445 * factor)
		stage_sum += 0.38491758704185486;
	else
		stage_sum += 0.5387271046638489;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 7.0, 2.0, 1.0, 3.0);
	if(sum < 0.004926044959574938 * factor)
		stage_sum += 0.4729771912097931;
	else
		stage_sum += 0.7447251081466675;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 19.0, 15.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 19.0, 5.0, 1.0, 3.0);
	if(sum < 0.0043908702209591866 * factor)
		stage_sum += 0.48091810941696167;
	else
		stage_sum += 0.5591921806335449;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 19.0, 15.0, 1.0, -1.0);
	sum += rect_sum_ii(6.0, 19.0, 5.0, 1.0, 3.0);
	if(sum < -0.017793629318475723 * factor)
		stage_sum += 0.6903678178787231;
	else
		stage_sum += 0.46769270300865173;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 13.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 14.0, 2.0, 1.0, 3.0);
	if(sum < 0.002046966925263405 * factor)
		stage_sum += 0.5370690226554871;
	else
		stage_sum += 0.33081620931625366;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 0.0, 4.0, 15.0, -1.0);
	sum += rect_sum_ii(7.0, 0.0, 2.0, 15.0, 2.0);
	if(sum < 0.029891489073634148 * factor)
		stage_sum += 0.5139865279197693;
	else
		stage_sum += 0.3309059143066406;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 6.0, 2.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 1.0, 5.0, 2.0);
	if(sum < 0.0015494900289922953 * factor)
		stage_sum += 0.466023713350296;
	else
		stage_sum += 0.6078342795372009;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 2.0, 7.0, -1.0);
	sum += rect_sum_ii(10.0, 5.0, 1.0, 7.0, 2.0);
	if(sum < 0.001495696953497827 * factor)
		stage_sum += 0.44048359990119934;
	else
		stage_sum += 0.5863919854164124;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 11.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(16.0, 12.0, 3.0, 1.0, 3.0);
	if(sum < 0.0009588592802174389 * factor)
		stage_sum += 0.5435971021652222;
	else
		stage_sum += 0.42085230350494385;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 11.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 12.0, 3.0, 1.0, 3.0);
	if(sum < 0.0004964370164088905 * factor)
		stage_sum += 0.5370578169822693;
	else
		stage_sum += 0.4000622034072876;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 7.0, 8.0, 1.0, 3.0);
	if(sum < -0.00272808107547462 * factor)
		stage_sum += 0.5659412741661072;
	else
		stage_sum += 0.4259642958641052;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 15.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 16.0, 6.0, 1.0, 2.0);
	if(sum < 0.0023026480339467525 * factor)
		stage_sum += 0.5161657929420471;
	else
		stage_sum += 0.3350869119167328;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 18.0, 6.0, -1.0);
	sum += rect_sum_ii(7.0, 0.0, 6.0, 6.0, 3.0);
	if(sum < 0.25151631236076355 * factor)
		stage_sum += 0.48696619272232056;
	else
		stage_sum += 0.714730978012085;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 0.0, 1.0, 4.0, 3.0);
	if(sum < -0.004632802214473486 * factor)
		stage_sum += 0.27274489402770996;
	else
		stage_sum += 0.5083789825439453;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 10.0, 4.0, 10.0, -1.0);
	sum += rect_sum_ii(16.0, 10.0, 2.0, 5.0, 2.0);
	sum += rect_sum_ii(14.0, 15.0, 2.0, 5.0, 2.0);
	if(sum < -0.04043449088931084 * factor)
		stage_sum += 0.6851438879966736;
	else
		stage_sum += 0.5021767020225525;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 2.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(4.0, 2.0, 1.0, 2.0, 3.0);
	if(sum < 0.000014972220014897175 * factor)
		stage_sum += 0.428446501493454;
	else
		stage_sum += 0.5522555112838745;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 2.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 3.0, 2.0, 1.0, 2.0);
	if(sum < -0.00024050309730228037 * factor)
		stage_sum += 0.42261189222335815;
	else
		stage_sum += 0.5390074849128723;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 10.0, 4.0, 10.0, -1.0);
	sum += rect_sum_ii(2.0, 10.0, 2.0, 5.0, 2.0);
	sum += rect_sum_ii(4.0, 15.0, 2.0, 5.0, 2.0);
	if(sum < 0.023657839745283127 * factor)
		stage_sum += 0.47446319460868835;
	else
		stage_sum += 0.7504366040229797;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 13.0, 20.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 13.0, 10.0, 3.0, 2.0);
	sum += rect_sum_ii(0.0, 16.0, 10.0, 3.0, 2.0);
	if(sum < -0.00814491044729948 * factor)
		stage_sum += 0.42450588941574097;
	else
		stage_sum += 0.5538362860679626;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 2.0, 15.0, -1.0);
	sum += rect_sum_ii(1.0, 5.0, 1.0, 15.0, 2.0);
	if(sum < -0.003699213033542037 * factor)
		stage_sum += 0.5952357053756714;
	else
		stage_sum += 0.45297130942344666;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 18.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 9.0, 2.0, 2.0);
	sum += rect_sum_ii(1.0, 9.0, 9.0, 2.0, 2.0);
	if(sum < -0.0067718601785600185 * factor)
		stage_sum += 0.4137794077396393;
	else
		stage_sum += 0.5473399758338928;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 2.0, 17.0, -1.0);
	sum += rect_sum_ii(1.0, 0.0, 1.0, 17.0, 2.0);
	if(sum < 0.004266953095793724 * factor)
		stage_sum += 0.4484114944934845;
	else
		stage_sum += 0.5797994136810303;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 6.0, 16.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 8.0, 3.0, 2.0);
	sum += rect_sum_ii(2.0, 9.0, 8.0, 3.0, 2.0);
	if(sum < 0.0017791989957913756 * factor)
		stage_sum += 0.5624858736991882;
	else
		stage_sum += 0.44324448704719543;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 14.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 1.0, 1.0, 3.0);
	if(sum < 0.0016774770338088274 * factor)
		stage_sum += 0.4637751877307892;
	else
		stage_sum += 0.63642418384552;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 15.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 16.0, 4.0, 1.0, 2.0);
	if(sum < 0.0011732629500329494 * factor)
		stage_sum += 0.4544503092765808;
	else
		stage_sum += 0.5914415717124939;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 2.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 2.0, 4.0, 1.0, 2.0);
	sum += rect_sum_ii(9.0, 3.0, 4.0, 1.0, 2.0);
	if(sum < 0.000869981711730361 * factor)
		stage_sum += 0.5334752798080444;
	else
		stage_sum += 0.38859179615974426;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 11.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 14.0, 8.0, 3.0, 2.0);
	if(sum < 0.0007637834060005844 * factor)
		stage_sum += 0.5398585200309753;
	else
		stage_sum += 0.37449419498443604;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 13.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 14.0, 2.0, 1.0, 2.0);
	if(sum < 0.00015684569370932877 * factor)
		stage_sum += 0.43178731203079224;
	else
		stage_sum += 0.5614616274833679;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 4.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(18.0, 6.0, 2.0, 2.0, 3.0);
	if(sum < -0.021511370316147804 * factor)
		stage_sum += 0.1785925030708313;
	else
		stage_sum += 0.5185542702674866;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 12.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 13.0, 2.0, 1.0, 2.0);
	if(sum < 0.00013081369979772717 * factor)
		stage_sum += 0.4342499077320099;
	else
		stage_sum += 0.5682849884033203;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 4.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(18.0, 6.0, 2.0, 2.0, 3.0);
	if(sum < 0.021992040798068047 * factor)
		stage_sum += 0.5161716938018799;
	else
		stage_sum += 0.23793940246105194;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 13.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 14.0, 1.0, 1.0, 3.0);
	if(sum < -0.0008013650076463819 * factor)
		stage_sum += 0.598676323890686;
	else
		stage_sum += 0.4466426968574524;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 4.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(18.0, 6.0, 2.0, 2.0, 3.0);
	if(sum < -0.008273609913885593 * factor)
		stage_sum += 0.410821795463562;
	else
		stage_sum += 0.5251057147979736;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 4.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 6.0, 2.0, 2.0, 3.0);
	if(sum < 0.0036831789184361696 * factor)
		stage_sum += 0.5173814296722412;
	else
		stage_sum += 0.33975180983543396;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 12.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 13.0, 3.0, 1.0, 3.0);
	if(sum < -0.007952568121254444 * factor)
		stage_sum += 0.6888983249664307;
	else
		stage_sum += 0.48459240794181824;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 13.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 14.0, 2.0, 1.0, 3.0);
	if(sum < 0.0015382299898192286 * factor)
		stage_sum += 0.5178567171096802;
	else
		stage_sum += 0.34541139006614685;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 13.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 14.0, 4.0, 1.0, 3.0);
	if(sum < -0.014043530449271202 * factor)
		stage_sum += 0.1678421050310135;
	else
		stage_sum += 0.518866777420044;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 5.0, 3.0, 1.0, 3.0);
	if(sum < 0.0014315890148282051 * factor)
		stage_sum += 0.436825692653656;
	else
		stage_sum += 0.5655773878097534;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 2.0, 10.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 4.0, 10.0, 2.0, 3.0);
	if(sum < -0.034014228731393814 * factor)
		stage_sum += 0.7802296280860901;
	else
		stage_sum += 0.49592170119285583;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 13.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 14.0, 4.0, 1.0, 3.0);
	if(sum < -0.012027299962937832 * factor)
		stage_sum += 0.15851010382175446;
	else
		stage_sum += 0.503223180770874;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 7.0, 15.0, 5.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 5.0, 5.0, 3.0);
	if(sum < 0.13316619396209717 * factor)
		stage_sum += 0.5163304805755615;
	else
		stage_sum += 0.27551281452178955;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 7.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 7.0, 4.0, 2.0, 3.0);
	if(sum < -0.0015221949433907866 * factor)
		stage_sum += 0.372831791639328;
	else
		stage_sum += 0.5214552283287048;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 3.0, 3.0, 9.0, -1.0);
	sum += rect_sum_ii(11.0, 3.0, 1.0, 9.0, 3.0);
	if(sum < -0.000939292716793716 * factor)
		stage_sum += 0.5838379263877869;
	else
		stage_sum += 0.45111650228500366;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 6.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 2.0, 6.0, 2.0);
	if(sum < 0.027719739824533463 * factor)
		stage_sum += 0.4728286862373352;
	else
		stage_sum += 0.7331544756889343;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 8.0, 4.0, 1.0, 3.0);
	if(sum < 0.003103015013039112 * factor)
		stage_sum += 0.5302202105522156;
	else
		stage_sum += 0.4101563096046448;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 9.0, 4.0, 9.0, -1.0);
	sum += rect_sum_ii(2.0, 9.0, 2.0, 9.0, 2.0);
	if(sum < 0.07786121964454651 * factor)
		stage_sum += 0.4998334050178528;
	else
		stage_sum += 0.12729619443416595;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 13.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(10.0, 13.0, 1.0, 5.0, 3.0);
	if(sum < -0.015854939818382263 * factor)
		stage_sum += 0.050833359360694885;
	else
		stage_sum += 0.5165656208992004;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 7.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 2.0, 3.0, 3.0);
	if(sum < -0.00497253006324172 * factor)
		stage_sum += 0.6798133850097656;
	else
		stage_sum += 0.46842318773269653;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 5.0, 3.0);
	if(sum < -0.0009767650626599789 * factor)
		stage_sum += 0.6010771989822388;
	else
		stage_sum += 0.4788931906223297;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 4.0, 2.0, 2.0);
	if(sum < -0.0024647710379213095 * factor)
		stage_sum += 0.3393397927284241;
	else
		stage_sum += 0.5220503807067871;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 9.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 9.0, 4.0, 2.0, 3.0);
	if(sum < -0.006793770007789135 * factor)
		stage_sum += 0.4365136921405792;
	else
		stage_sum += 0.5239663124084473;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 10.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 5.0, 3.0, 2.0);
	if(sum < 0.032608021050691605 * factor)
		stage_sum += 0.505272388458252;
	else
		stage_sum += 0.2425214946269989;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 12.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(11.0, 12.0, 1.0, 1.0, 3.0);
	if(sum < -0.0005851442110724747 * factor)
		stage_sum += 0.5733973979949951;
	else
		stage_sum += 0.4758574068546295;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 1.0, 11.0, 15.0, -1.0);
	sum += rect_sum_ii(0.0, 6.0, 11.0, 5.0, 3.0);
	if(sum < -0.029632600024342537 * factor)
		stage_sum += 0.3892289102077484;
	else
		stage_sum += 0.5263597965240479;


	if(stage_sum > 66.66912078857422)
		return 1;
	else
		return 0;
}

vec4 HaarCascadeFrontalFaceAlt()
{
	float invArea = 1.0 / (scale * 20.0 * scale * 20.0);
	float mean = rect_sum_ii(v_texcoord.x, v_texcoord.y, 20.0, 20.0, invArea);
	float variance = rect_sum_ii2(v_texcoord.x, v_texcoord.y, 20.0, 20.0, invArea) - (mean * mean);
	float std = sqrt(variance);
	if(HaarCascadeFrontalFaceAlt_stage0(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage1(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage2(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage3(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage4(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage5(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage6(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage7(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage8(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage9(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage10(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage11(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage12(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage13(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeFrontalFaceAlt_stage14(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	return vec4(1.0, 1.0, 1.0, 1.0);
}

void main()
{
	gl_FragColor = HaarCascadeFrontalFaceAlt();
}
