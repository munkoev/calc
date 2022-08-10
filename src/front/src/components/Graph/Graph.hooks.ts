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
import { useAppDispatch, useAppSelector } from "../../app/hooks";
import axios from "axios";
import { addGraphSeries } from "../../app/graphSlice";

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
  useEffect(() => {
    const getSeries = async () => {

      const y =  await axios({
        method: 'GET',
        url:
          `http://185.195.25.140:3000/?` + 
          `string=${settings.func}`+
          `&xmin=${settings.x_min}`+
          `&xmax=${settings.x_max}`+
          `&step=${settings.step}`,
      })
      console.log(typeof y.data)
      // setSeries(JSON.parse(y.data));
    }
    getSeries();
  }, []);

  const dispatch = useAppDispatch();
  const onClickDrawHandler = () => {
    dispatch(addGraphSeries(series))
  }

  const options: ChartOptions<"line"> = {
    responsive: true,
    plugins: {
      legend: {
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

  const labels = (new Array(settings.x_max - settings.x_min + 1)).map((e, i) => settings.x_min + i);

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

  return { options, data };
};

export default useGraphHook;
