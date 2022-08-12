import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";

import type { ChartData, ChartOptions } from "chart.js";
import { useEffect, useState } from "react";
import { useAppSelector } from "../../app/hooks";
import axios from "axios";
// import { addGraphSeries } from "../../app/graphSlice";

const useGraphHook = () => {
  ChartJS.register(
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend
  );
  const settings = useAppSelector(state => state.graph.settings)
  const [series, setSeries] = useState([] as any[])
  const [err, setErr] = useState(false)
  useEffect(() => {
    const getSeries = async () => {
      const url_encoded = 
        `http://185.195.25.140:3000/?` + 
        `string=${encodeURIComponent(settings.func)}`+
        `&xmin=${settings.x_min}`+
        `&xmax=${settings.x_max}`+
        `&step=${settings.step}`

        try {
          const y =  await axios({
            method: 'GET',
            url: url_encoded,
          })
          setSeries(y.data.points);
          setErr(false)
        } catch {
          setSeries([])
          setErr(true)
        }
    }
    getSeries();
  }, [settings]);

  // const dispatch = useAppDispatch();
  // const onClickDrawHandler = () => {
  //   dispatch(addGraphSeries(series))
  // }

  const options: ChartOptions<"line"> = {
    responsive: true,
    showLine: false,
    plugins: {
      legend: {
        display: false,
        position: "top" as const,
      },
      title: {
        display: false,
        text: "Chart.js Line Chart",
      },
    },
    scales: {
      x: {
        type: "linear",
        min: settings.x_min,
        max: settings.x_max,
        grid: {
          display: true,
        },
        title: {
          display: false,
          text: "xaxis title",
        },
        position: "center",
      },
      y: {
        min: settings.y_min,
        max: settings.y_max,
        grid: {
          display: true,
        },
        title: {
          display: false,
          text: "yaxis title",
        },
        position: "center",
      },
    },

  };

  const labels = (new Array(
    Math.ceil((settings.x_max - settings.x_min + 1)/settings.step)
    )).map((e, i) => settings.x_min + i);

  const data: ChartData<"line"> = {
    labels,
    datasets: [
      {
        label: "Dataset 1",
        data: series,
        borderColor: "rgb(255, 99, 132)",
        backgroundColor: "rgba(255, 99, 132, 0.5)",
        cubicInterpolationMode: "monotone",
      },
      // {
      //   label: "",
      //   data: [-5, 5, -5, 5, -5, 5, 5],
      //   borderColor: "rgb(53, 162, 235)",
      //   backgroundColor: "rgba(53, 162, 235, 0.5)",
      // },
    ],
  };

  return { options, data, err };
};

export default useGraphHook;
