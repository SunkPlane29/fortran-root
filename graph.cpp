#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TRootCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::string> getGraphFiles(int argc, char **argv) {
	std::vector<std::string> files;
	files.reserve(argc - 1);

	for (int i = 1; i < argc; i++) {
		files.push_back(std::string(argv[i]));
	}

	return files;
}

TMultiGraph* createGraph(std::vector<std::string> files) {
	TMultiGraph *mg = new TMultiGraph();

	int i = 2;

	for (const auto& file : files) {
		TGraph *graph = new TGraph(file.c_str(), "%lg %lg");
		graph->SetTitle(("Function graph define by data file " + file).c_str());
		graph->SetLineWidth(3);
		graph->SetMarkerStyle(i);
		graph->SetMarkerSize(1);
		mg->Add(graph, "PL");

		i += 2;
	}

	return mg;
}

//TODO: make multicolred graphs to distinguish them, and maybe labels
int main(int argc, char **argv) {
	TApplication app("app", &argc, argv);
	TCanvas *c = new TCanvas("c", "Something", 0, 0, 800, 600);

	std::vector<std::string> files = getGraphFiles(app.Argc(), app.Argv());

	gStyle->SetOptTitle(kFALSE);
	gStyle->SetPalette(kSolar);

	TMultiGraph *graph = createGraph(files);
	graph->SetTitle("Graph; x; f(x)");
	graph->Draw("as pmc plc");

	gPad->BuildLegend();

	c->Modified(); c->Update();
	TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

	app.Run();

	return 0;
}

