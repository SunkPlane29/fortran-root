//this application allows the user to build it's owns graphs from datasets
//(.dat) files that can be created with fortran (and possibly other languages)
//and basically works like gnuplot, except it is based on the ROOT framework
//developed by CERN
//
//so far there is no real benefict of working with root, except learning it
//but for more complex applications that involve more complex plots, it could
//be a good option.
//
//remember: GOD is REAL (unless declared INTEGER)

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
#include <memory>

std::vector<std::string> getGraphFiles(int argc, char **argv) {
	std::vector<std::string> files;
	files.reserve(argc - 1);

	for (int i = 1; i < argc; i++) {
		files.push_back(std::string(argv[i]));
	}

	return files;
}

std::unique_ptr<TMultiGraph> createGraph(std::vector<std::string> files) {
	auto mg = std::make_unique<TMultiGraph>();

	int i = 2;

	for (const auto& file : files) {
		// this is only safe in terms of memory because according to the definition of
		// TMultiGraph it owns the graphs so there should be no need to manage this
		// resource, since when TMultiGraph is delete, so will it's underlying graphs
		TGraph *graph = new TGraph(file.c_str(), "%lg %lg");
		graph->SetTitle(("Function graph define by data file " + file).c_str());
		graph->SetLineWidth(3);
		graph->SetMarkerStyle(i);
		graph->SetMarkerSize(1);
		graph->SetEditable(kFALSE);
		mg->Add(graph, "PL");

		i += 2;
	}

	return mg;
}

int main(int argc, char **argv) {
	TApplication app("app", &argc, argv);
	auto c = std::make_unique<TCanvas>("c", "Graph", 0, 0, 800, 600);

	std::vector<std::string> files = getGraphFiles(app.Argc(), app.Argv());

	gStyle->SetOptTitle(kFALSE);
	gStyle->SetPalette(kSolar);

	std::unique_ptr<TMultiGraph> graph = createGraph(files);
	graph->SetTitle("Graph; x; f(x)");
	graph->Draw("as pmc plc");

	gPad->BuildLegend();

	c->Modified(); c->Update();
	TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

	app.Run();

	return 0;
}

