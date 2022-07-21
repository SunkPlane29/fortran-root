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
		if (argv[i][0] == '-') {
			continue;
		}
		files.push_back(std::string(argv[i]));
	}

	return files;
}

std::string getFlag(int argc, char **argv, const char *flag) {
	std::string flag_val = "";

	for (int i = 1; i < argc; i++) {
	    std::string arg_string = argv[i];
		size_t arg_pos = arg_string.find(flag);
		if (arg_pos != std::string::npos) {
			size_t flag_val_pos = arg_string.find("=")+1;
			flag_val = arg_string.substr(flag_val_pos);
		}
    }

    return flag_val;
}

bool get_marker_set(int argc, char **argv) {
	std::string marker_set_flag = getFlag(argc, argv, "-marker");
	std::cout << marker_set_flag;

	if (marker_set_flag == "off") {
		return false;
	}

	return true;
}

struct GraphOptions {
	bool ShowMarker;
}

const DefaultGraphOptions = GraphOptions{.ShowMarker = true};

std::unique_ptr<TMultiGraph> createGraph(std::vector<std::string> files, GraphOptions graph_opt = DefaultGraphOptions) {
	auto mg = std::make_unique<TMultiGraph>();

	int i = 2;

	for (const auto& file : files) {
		// this is only safe in terms of memory because according to the definition of
		// TMultiGraph it owns the graphs so there should be no need to manage this
		// resource, since when TMultiGraph is delete, so will it's underlying graphs
		TGraph *graph = new TGraph(file.c_str(), "%lg %lg");
		graph->SetTitle(("Function graph define by data file " + file).c_str());

		graph->SetLineWidth(3);
		graph->SetLineStyle(i);

		graph->SetMarkerStyle(i);
		graph->SetMarkerSize(1);

		if (!graph_opt.ShowMarker) {
			graph->SetMarkerStyle(0);
			graph->SetMarkerSize(0);
		}

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

	GraphOptions graph_opt = DefaultGraphOptions;
	if (!get_marker_set(argc, argv)) {
		graph_opt.ShowMarker = false;
	}

	std::unique_ptr<TMultiGraph> graph = createGraph(files, graph_opt);
	graph->SetTitle("Graph; x; f(x)");
	graph->Draw("as pmc plc");

	gPad->BuildLegend();

	c->Modified(); c->Update();
	TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

	app.Run();

	return 0;
}

