import { createSlice } from '@reduxjs/toolkit'

interface IinitialState {
    settings: {
        x: number,
        x_min: number,
        x_max: number,
        y_min: number,
        y_max: number,
        step: number,
        func: string
    },
    points: number[][]
}

const initialState: IinitialState = {
    settings: {
        x: 0,
        x_min: -0.2,
        x_max: 0.2,
        y_min: -0.03,
        y_max: 0.03,
        step: 0.001,
        func: 'x^2*sin(1/x)'
    },
    points: [[0,0]]
}

export const graphSlice = createSlice({
    name: 'graph',
    initialState,
    reducers: {
        getInput: (state, action) => {
            console.log(action.payload)
            // state.settings.x = action.payload.x;
            if (action.payload.x_min) state.settings.x_min = action.payload.x_min;
            if (action.payload.x_max) state.settings.x_max = action.payload.x_max;
            if (action.payload.y_min) state.settings.y_min = action.payload.y_min;
            if (action.payload.y_max) state.settings.y_max = action.payload.y_max;
            // state.settings.y_min = action.payload.y_min;
            // state.settings.y_max = action.payload.y_max;
            if (action.payload.func) state.settings.func = action.payload.func
            if (action.payload.step) state.settings.step = action.payload.step
        },
        addGraphSeries: (state, action) => {

        }
    }
})

export const {getInput, addGraphSeries} = graphSlice.actions;
export default graphSlice.reducer;