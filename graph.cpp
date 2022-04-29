#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TRootCanvas.h"

int main(int argc, char **argv) {
	TApplication app("app", &argc, argv);
	TCanvas *c = new TCanvas("c", "Something", 0, 0, 800, 600);

	TGraph *graph = new TGraph("./graph.dat", "%lg %lg");
	graph->SetFillColor(kYellow+1);
  graph->SetLineColor(kYellow+1);
  graph->SetMarkerColor(kYellow+1);
	graph->SetTitle("Graph; x; y");
	graph->Draw();

	c->Modified(); c->Update();
	TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

	app.Run();

	return 0;
}

